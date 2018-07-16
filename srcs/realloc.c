/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 18:47:18 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 16:45:14 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void 	*expand_chunk(t_chunk_find chunk, t_chunk_types *chunks, size_t size)
{
	void	*pointer;
	void	*chunk_copy;

	chunk_copy = (void *)(chunk.chunk);
	if ((pointer = init_chunks(chunks, size)) == NULL)
		return (NULL);
	pointer = (void *)pointer + sizeof(t_chunk);
	ft_memcpy(pointer, chunk_copy + sizeof(t_chunk), chunk.chunk->size);
	free2(chunk_copy + sizeof(t_chunk));
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
		chunk_size += pointer->size + sizeof(t_chunk);
		pointer = pointer->next;
	}
	if (size <= match->size || (match->next == NULL &&
			chunk.chunk->chunk_size - chunk_size + match->size >= size))
	{
		match->freed = 0;
		match->size = size;
	}
	else
		return (expand_chunk(chunk, chunks, size));
	return ((void *)match + sizeof(t_chunk));
}

