/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 17:53:36 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 17:59:13 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk *(g_chunks[3]) = {NULL, NULL, NULL};

size_t    get_chunk_size(size_t size, int page_size) {
    return ((size + (page_size - 1)) & -page_size);
}

t_chunk   *create_chunk(t_chunk **chunk, size_t size, int chunk_size) {
    if ((*chunk = mmap(NULL, chunk_size,
  PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
      return (NULL);
    (*chunk)->freed = 0;
    (*chunk)->size = size;
    (*chunk)->next = NULL;
    return (*chunk);
}

t_chunk   *append_chunk(t_chunk *chunk, size_t size)
{
    t_chunk new_chunk;

    new_chunk.freed = 0;
    new_chunk.size = size;
    new_chunk.next = chunk->next;
    chunk->next = ((void *)chunk) + chunk->size + sizeof(t_chunk);
    ft_memcpy(chunk->next, &new_chunk, sizeof(t_chunk));
    return (chunk->next);
}

t_chunk   *get_next_chunk(t_chunk *chunk, size_t size, size_t chunk_size)
{
    size_t  total;
    t_chunk *new_chunk;

    total = 0;
    while (chunk->next != NULL)
    {
      if (total + chunk->size + sizeof(t_chunk) > chunk_size &&
        total + size + sizeof(t_chunk) < chunk_size)
        return (append_chunk(chunk, size));
      total += chunk->size + sizeof(t_chunk);
      if (total > chunk_size)
        total = chunk->size + sizeof(t_chunk);
      chunk = chunk->next;
    }
    if (total + size + sizeof(t_chunk) * 2 + chunk->size <= chunk_size)
      return (append_chunk(chunk, size));
    if ((new_chunk = create_chunk((t_chunk **)(&(chunk->next)), size, chunk_size)) == NULL)
      return (NULL);
    chunk->next = new_chunk;
    return (new_chunk);
}

t_chunk   *big_chunk(t_chunk **chunk, size_t size)
{
    t_chunk *tmp;

    if (*chunk == NULL)
      return (create_chunk(chunk, size, get_chunk_size(size, getpagesize())));
    tmp = *chunk;
    while (tmp->next != NULL)
      tmp = tmp->next;
    return (create_chunk(((t_chunk **)(&(tmp->next))), size, get_chunk_size(size, getpagesize())));
}

t_chunk			*init_chunks(size_t size)
{
    size_t	max_tiny;
    size_t      max_small;
    int 	page_size;

    page_size = getpagesize();
    max_tiny = page_size * TINY / 100 - sizeof(t_chunk);
    max_small = page_size * SMALL / 100 - sizeof(t_chunk);
    if (size <= max_tiny && g_chunks[0] == NULL)
      return (create_chunk(&(g_chunks[0]), size, page_size * TINY));
    else if (size <= max_tiny && g_chunks[0] != NULL)
      return (get_next_chunk(g_chunks[0], size, page_size * TINY));
    else if (size <= max_small && g_chunks[1] == NULL)
      return (create_chunk(&(g_chunks[1]), size, page_size * SMALL));
    else if (size <= max_small && g_chunks[1] != NULL)
      return (get_next_chunk(g_chunks[1], size, page_size * SMALL));
    return (big_chunk(&(g_chunks[2]), size));
}

void    *malloc(size_t size)
{
    return (((void *)init_chunks(size)) + sizeof(t_chunk));
}

void    free_in_chunk(t_chunk *chunk, t_chunk **chunks, int type)
{
    t_chunk   *tmp;
    size_t    total;
    size_t    page_size;
    t_chunk   *previous;
    size_t    page_freed;

    total = 0;
    tmp = *chunks;
    page_freed = 1;
    previous = NULL;
    page_size = getpagesize();
    while (tmp != chunk)
    {
      if (!tmp->freed)
        page_freed = 0;
      total += tmp->size + sizeof(t_chunk);
      if (total > page_size * type)
      {
        previous = ((void *)tmp) - total;
        total = tmp->size + sizeof(t_chunk);
      }
      tmp = tmp->next;
    }
    tmp->freed = 1;
    while (tmp != NULL && total + tmp->size + sizeof(t_chunk) < page_size * type)
    {
      if (!tmp->freed)
        page_freed = 0;
      tmp = tmp->next;
      total += tmp->size + sizeof(t_chunk);
    dprintf(1, "HelloWorld\n");
    }
    if (page_freed)
    {
      if (previous == NULL)
        *chunks = tmp->next;
      else
        previous->next = tmp->next;
      tmp = ((void *)tmp) - total;
      munmap(tmp, get_chunk_size(tmp->size, page_size * type));
    }
}

void    free_chunk(t_chunk *chunk, t_chunk **chunks, int type)
{
    t_chunk *tmp;
    t_chunk *previous;

    tmp = *chunks;
    if (type == -1)
    {
      previous = NULL;
      while (tmp != chunk)
      {
        previous = tmp;
        tmp = tmp->next;
      }
      if (previous == NULL)
        *chunks = NULL;
      else
        previous->next = chunk->next;
      munmap(chunk, chunk->size);
    }
    else
      free_in_chunk(chunk, chunks, type);
}

void    free(void *ptr)
{
    t_chunk *chunk;
    size_t  max_tiny;
    size_t  max_small;
    int     page_size;

    if (ptr == NULL)
      return ;
    chunk = ptr - sizeof(t_chunk);
    chunk->freed = 1;
    page_size = getpagesize();
    max_tiny = page_size * TINY / 100 - sizeof(t_chunk);
    max_small = page_size * SMALL / 100 - sizeof(t_chunk);
    if (get_chunk_size(chunk->size, page_size * TINY) <= max_tiny)
      free_chunk(chunk, &(g_chunks[0]), TINY);
    else if (get_chunk_size(chunk->size, page_size * SMALL) >= max_tiny && chunk->size >= max_small)
      free_chunk(chunk, &(g_chunks[1]), SMALL);
    else
      free_chunk(chunk, &(g_chunks[2]), -1);
}

void    show_alloc_mem(void)
{
    print_alloc_mem(g_chunks);
}

