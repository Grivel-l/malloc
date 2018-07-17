/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chunks_free.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 08:17:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 15:21:45 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void		find_chunk(t_chunk_find *chunk, t_chunk	*chunks, void *ptr)
{
	t_chunk	*chunk_start;

	chunk->next = NULL;
	chunk->chunk = NULL;
	chunk->previous = NULL;
	while (chunks != NULL)
	{
		if (chunks->chunk_size != 0)
		{
			chunk->freeable = 1;
			chunk_start = chunks;
		}
		if ((void *)chunks + sizeof(t_chunk) == ptr)
		{
			chunks->freed = 1;
			chunk->chunk = chunk_start;
		}
		else
			if (!chunks->freed)
				chunk->freeable = 0;
		if (chunk->chunk == NULL)
			chunk->previous = chunks;
		chunks = chunks->next;
		if (chunks != NULL && chunks->chunk_size != 0)
		{
			if (chunk->chunk != NULL)
			{
				chunk->next = chunks;
				break ;
			}
		}
	}
}

t_chunk_find	*get_chunk(t_chunk_find *chunk, t_chunk_types *chunks, void *ptr)
{
	find_chunk(chunk, chunks->tiny, ptr);
	if (chunk->chunk != NULL)
		return (chunk);
	find_chunk(chunk, chunks->small, ptr);
	if (chunk->chunk != NULL)
		return (chunk);
	find_chunk(chunk, chunks->large, ptr);
	if (chunk->chunk != NULL)
		return (chunk);
	return (NULL);
}

void			free_pointer(t_chunk_types *chunks, t_chunk_find chunk)
{
	if (chunk.chunk == chunks->tiny)
		chunks->tiny = chunk.next;
	else if (chunk.chunk == chunks->small)
		chunks->small = chunk.next;
	else if (chunk.chunk == chunks->large)
		chunks->large = chunk.next;
	else
		chunk.previous->next = chunk.next;
	munmap(chunk.chunk, chunk.chunk->chunk_size);
}
