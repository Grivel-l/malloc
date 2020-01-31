/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/13 00:36:51 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/13 00:36:53 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <signal.h>
#include "malloc.h"

static void	free_page(t_chunk *previous, t_chunk **chunks,
		t_chunk **tmp, size_t total[2])
{
	if ((*tmp)->next == NULL)
		return ;
	if (previous == NULL)
		*chunks = (*tmp)->next;
	else
		previous->next = (*tmp)->next;
	*tmp = ((void *)(*tmp)) - total[0];
	munmap(*tmp, get_chunk_size((*tmp)->size, total[1]));
}

static void	free_in_chunk(t_chunk *chunk,
		t_chunk **chunks, size_t chunk_size)
{
	t_chunk	*tmp;
	size_t	total[2];
	t_chunk	*previous;
	size_t	page_freed;

	total[0] = 0;
	total[1] = chunk_size;
	tmp = *chunks;
	page_freed = 1;
	previous = NULL;
	while (tmp != chunk)
	{
		if (!tmp->freed)
			page_freed = 0;
		total[0] += tmp->size + sizeof(t_chunk);
		if (total[0] > chunk_size)
		{
			page_freed = 1;
			previous = ((void *)tmp) - total[0];
			total[0] = tmp->size + sizeof(t_chunk);
		}
		tmp = tmp->next;
	}
	if (check_freed(&tmp, total[0], page_freed, chunk_size))
		free_page(previous, chunks, &tmp, total);
}

static void	free_chunk(t_chunk *chunk, t_chunk **chunks, int type)
{
	t_chunk	*tmp;
	t_chunk	*previous;

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
			*chunks = tmp->next;
		else
			previous->next = chunk->next;
		if (previous != NULL)
			munmap(chunk, chunk->size);
	}
	else
		free_in_chunk(chunk, chunks, getpagesize() * type);
}

static int	check(void *ptr)
{
	t_chunk	*chunk;

	chunk = g_chunks[0];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	chunk = g_chunks[1];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	chunk = g_chunks[2];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	return (1);
}

void		free(void *ptr)
{
	int		type;
	t_chunk	*chunk;

	if (ptr == NULL)
		return ;
	if (check(ptr))
		return ;
	chunk = ptr - sizeof(t_chunk);
	chunk->freed = 1;
	type = get_type(chunk->size);
	if (type == TINY)
		free_chunk(chunk, &(g_chunks[0]), TINY);
	else if (type == SMALL)
		free_chunk(chunk, &(g_chunks[1]), SMALL);
	else
		free_chunk(chunk, &(g_chunks[2]), -1);
}
