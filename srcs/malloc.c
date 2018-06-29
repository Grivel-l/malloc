/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/17 23:31:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 17:32:51 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk_types	g_chunks = {NULL, NULL, NULL};

void					*malloc(size_t size)
{
	t_chunk	*chunk;

	if ((chunk = init_chunks(&g_chunks, size)) == NULL)
		return (NULL);
	return ((void *)chunk + sizeof(t_chunk));
}

void					free(void *ptr)
{
	t_chunk_free	chunk;

	if (get_chunk(&chunk, &g_chunks, ptr) != NULL)
	{
		if (chunk.freeable)
			free_pointer(&g_chunks, chunk);
	}
	else
	{
		write(1, strerror(errno), strlen(strerror(errno)));
		write(1, "Pointer\n", 8);
	}
}
