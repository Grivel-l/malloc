/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chunks_free.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 08:17:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 08:42:58 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*find_chunk(t_chunk *chunks, t_chunk **previous, void *ptr)
{
	while (chunks != NULL)
	{
		if (chunks + sizeof(t_chunk) == ptr)
			return (chunks);
		*previous = chunks;
		chunks = chunks->next;
	}
	return (NULL);
}

t_chunk		*get_chunk(t_chunk_types chunks, t_chunk **previous, void *ptr)
{
	t_chunk		*chunk;

	if ((chunk = find_chunk(chunks.tiny, previous, ptr)) != NULL)
		return (chunk);
	else if ((chunk = find_chunk(chunks.small, previous, ptr)) != NULL)
		return (chunk);
	else if ((chunk = find_chunk(chunks.large, previous, ptr)) != NULL)
		return (chunk);
	return (NULL);
}
