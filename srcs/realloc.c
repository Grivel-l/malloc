/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 18:47:18 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 23:35:02 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void 	*expand_chunk(t_chunk_find chunk, t_chunk_types *chunks, size_t size)
{
	void	*pointer;

	if ((pointer = init_chunks(chunks, size)) == NULL)
		return (NULL);
	ft_memcpy(pointer + sizeof(t_chunk), (void *)(chunk.chunk) + sizeof(t_chunk), chunk.chunk->size);
	chunk.chunk->freed = 1;
	free_pointer(chunks, chunk);
	return (pointer);
}

void			*realloc_chunk(t_chunk_types *chunks,
			t_chunk_find chunk, void *ptr, size_t size)
{
	t_chunk		*match;
	t_chunk		*pointer;
	size_t		chunk_size;

	chunk_size = 0;
	pointer = chunk.chunk;
	while (pointer != NULL)
	{
		if ((void *)pointer + sizeof(t_chunk) == ptr)
			match = pointer;
		chunk_size += pointer->size;
		pointer = pointer->next;
	}
	if (match->next == NULL &&
		chunk_size + sizeof(t_chunk) + size > chunk.chunk->chunk_size)
		chunk.chunk->size = size;
	else
		return (expand_chunk(chunk, chunks, size));
	return (chunk.chunk);
}

