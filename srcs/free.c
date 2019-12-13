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

static void	free_in_chunk(t_chunk *chunk, t_chunk **chunks, int type)
{
	t_chunk	*tmp;
	size_t	total;
	size_t	page_size;
	t_chunk	*previous;
	size_t	page_freed;

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
	while (tmp->next != NULL &&
	total + tmp->size + sizeof(t_chunk) < page_size * type)
	{
		if (!tmp->freed)
			page_freed = 0;
		tmp = tmp->next;
		total += tmp->size + sizeof(t_chunk);
	}
	if (!tmp->freed)
		page_freed = 0;
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
		free_in_chunk(chunk, chunks, type);
}

void		free(void *ptr)
{
	int		type;
	t_chunk	*chunk;

	chunk = g_chunks[0];
	if (ptr == NULL)
		return ;
	chunk = ptr - sizeof(t_chunk);
	chunk->freed = 1;
	type = get_type(chunk);
	if (type == TINY)
		free_chunk(chunk, &(g_chunks[0]), TINY);
	else if (type == SMALL)
		free_chunk(chunk, &(g_chunks[1]), SMALL);
	else
		free_chunk(chunk, &(g_chunks[2]), -1);
}
