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

#include "malloc.h"

static int	check_freed(t_chunk **tmp, size_t total,
size_t page_freed, size_t chunk_size)
{
	(*tmp)->freed = 1;
	while ((*tmp)->next != NULL &&
	total + (*tmp)->size + sizeof(t_chunk) < chunk_size)
	{
		if (!(*tmp)->freed)
			page_freed = 0;
		(*tmp) = (*tmp)->next;
		total += (*tmp)->size + sizeof(t_chunk);
	}
	if (!(*tmp)->freed)
		page_freed = 0;
	return (page_freed);
}

static void	free_page(t_chunk *previous, t_chunk **chunks,
t_chunk **tmp, size_t total, size_t chunk_size)
{
	if (previous == NULL)
		*chunks = (*tmp)->next;
	else
		previous->next = (*tmp)->next;
	*tmp = ((void *)(*tmp)) - total;
	munmap(*tmp, get_chunk_size((*tmp)->size, chunk_size));
}

static void	free_in_chunk(t_chunk *chunk,
t_chunk **chunks, size_t chunk_size)
{
	t_chunk	*tmp;
	size_t	total;
	t_chunk	*previous;
	size_t	page_freed;

	total = 0;
	tmp = *chunks;
	page_freed = 1;
	previous = NULL;
	while (tmp != chunk)
	{
		if (!tmp->freed)
			page_freed = 0;
		total += tmp->size + sizeof(t_chunk);
		if (total > chunk_size)
		{
			previous = ((void *)tmp) - total;
			total = tmp->size + sizeof(t_chunk);
		}
		tmp = tmp->next;
	}
	if (check_freed(&tmp, total, page_freed, chunk_size))
		free_page(previous, chunks, &tmp, total, chunk_size);
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
		munmap(chunk, chunk->size);
	}
	else
		free_in_chunk(chunk, chunks, getpagesize() * type);
}

void		free(void *ptr)
{
	int		type;
	t_chunk	*chunk;

	if (ptr == NULL)
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
