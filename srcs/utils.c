/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/13 00:39:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/13 00:39:31 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_chunk_size(size_t size, int page_size)
{
	return ((size + (page_size - 1)) & -page_size);
}

int		get_type(t_chunk *chunk)
{
	size_t	max_tiny;
	size_t	max_small;
	int		pagesize;

	pagesize = getpagesize();
	max_tiny = pagesize * TINY / 100 - sizeof(t_chunk);
	max_small = pagesize * SMALL / 100 - sizeof(t_chunk);
	if (chunk->size <= max_tiny)
		return (TINY);
	else if (chunk->size > max_tiny && chunk->size <= max_small)
		return (SMALL);
	return (-1);
}

t_chunk	*get_base_chunk(t_chunk *chunk, int type)
{
	size_t	total;
	t_chunk	*chunks;
	size_t	chunk_size;

	total = 0;
	if (type == TINY)
		chunks = g_chunks[0];
	else if (type == SMALL)
		chunks = g_chunks[1];
	else
		chunks = g_chunks[2];
	chunk_size = get_chunk_size(chunk->size, getpagesize());
	while (chunks != chunk)
	{
		total += chunks->size + sizeof(t_chunk);
		if (total > chunk_size)
			total = chunk->size + sizeof(t_chunk);
		chunks = chunks->next;
	}
	return (((void *)chunks) - total);
}
