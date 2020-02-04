/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/13 00:44:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/13 00:44:47 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_chunk *(g_chunks[3]) = {NULL, NULL, NULL};

static t_chunk	*create_chunk(t_chunk **chunk, size_t size, int chunk_size)
{
	if ((*chunk = mmap(NULL, chunk_size,
PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	(*chunk)->freed = 0;
	(*chunk)->size = size;
	(*chunk)->next = NULL;
	return (*chunk);
}

static size_t align(size_t size, size_t alignment) {
  return ((size + (alignment - 1)) & -alignment);
}

static t_chunk	*append_chunk(t_chunk *chunk, size_t size)
{
	t_chunk	new_chunk;

	new_chunk.freed = 0;
	new_chunk.size = size;
	new_chunk.next = chunk->next;
	chunk->next = ((void *)chunk) + chunk->size + sizeof(t_chunk);
	memcpy(chunk->next, &new_chunk, sizeof(t_chunk));
	return (chunk->next);
}

static t_chunk	*get_next_chunk(t_chunk *chunk, size_t size, size_t chunk_size)
{
	size_t	total;
	t_chunk	*previous;

	total = 0;
	previous = NULL;
	while (chunk != NULL)
	{
		if (total + chunk->size + sizeof(t_chunk) > chunk_size &&
				total + size + sizeof(t_chunk) <= chunk_size)
			return (append_chunk(previous, size));
		/* if (size <= chunk->size && chunk->freed) */
		/* { */
		/* 	chunk->freed = 0; */
		/* 	return (chunk); */
		/* } */
		total = total > chunk_size ?
chunk->size + sizeof(t_chunk) : total + chunk->size + sizeof(t_chunk);
		previous = chunk;
		chunk = chunk->next;
	}
	chunk = previous;
	if (total + size + sizeof(t_chunk) <= chunk_size)
		return (append_chunk(chunk, size));
	return (create_chunk((t_chunk **)(&(chunk->next)), size, chunk_size));
}

static t_chunk	*big_chunk(t_chunk **chunk, size_t size)
{
	t_chunk	*tmp;

	if (*chunk == NULL)
	{
		return (create_chunk(chunk,
size, get_chunk_size(size + sizeof(t_chunk), getpagesize())));
	}
	tmp = *chunk;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (create_chunk(((t_chunk **)(&(tmp->next))),
				size, get_chunk_size(size + sizeof(t_chunk), getpagesize())));
}

void                    *calloc(size_t count, size_t size) {
        void  *yo;

        yo = malloc(count * size);
        memset(yo, 0, count * size);
        return (yo);
}

void			*malloc(size_t size)
{
	t_chunk	*chunk;
	size_t	max_tiny;
	size_t	max_small;
	int		page_size;

        size = align(size, 16);
	page_size = getpagesize();
	max_tiny = page_size * TINY / 100 - sizeof(t_chunk);
	max_small = page_size * SMALL / 100 - sizeof(t_chunk);
	if (size <= max_tiny && g_chunks[0] == NULL)
		chunk = create_chunk(&(g_chunks[0]), size, page_size * TINY);
	else if (size <= max_tiny && g_chunks[0] != NULL)
		chunk = get_next_chunk(g_chunks[0], size, page_size * TINY);
	else if (size <= max_small && g_chunks[1] == NULL)
		chunk = create_chunk(&(g_chunks[1]), size, page_size * SMALL);
	else if (size <= max_small && g_chunks[1] != NULL)
		chunk = get_next_chunk(g_chunks[1], size, page_size * SMALL);
	else
		chunk = big_chunk(&(g_chunks[2]), size);
	if (chunk == NULL)
		return (NULL);
	return (((void *)chunk) + sizeof(t_chunk));
}
