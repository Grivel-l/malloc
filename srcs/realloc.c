/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/13 00:47:41 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/13 00:47:44 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void    *realloc(void *ptr, size_t size)
{
    t_chunk *base;
    t_chunk *chunk;

    if (ptr == NULL)
      return (malloc(size));
    if (size == 0 && ptr != NULL)
    {
      free(ptr);
      return (malloc(size));
    }
    chunk = ptr - sizeof(t_chunk);
    base = get_base_chunk(chunk, get_type(chunk));
    if (size + sizeof(t_chunk) <= get_chunk_size(base->size, getpagesize()) &&
      (chunk->next == NULL || chunk->next > ((void *)chunk) + size + sizeof(t_chunk)))
    {
      chunk->size = size;
      return (ptr);
    }
    if ((base = malloc(size)) == NULL)
      return (NULL);
    ft_memcpy(base, ptr, chunk->size);
    free(ptr);
    return (base);
}

