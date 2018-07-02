/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/17 23:31:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 23:24:24 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk_types	g_chunks = {NULL, NULL, NULL};

void					*malloc2(size_t size)
{
	t_chunk	*chunk;

	if ((chunk = init_chunks(&g_chunks, size)) == NULL)
		return (NULL);
	return ((void *)chunk + sizeof(t_chunk));
}

void					free2(void *ptr)
{
	t_chunk_find	chunk;

	if (ptr == NULL)
		return ;
	if (get_chunk(&chunk, &g_chunks, ptr) != NULL)
	{
		chunk.chunk->freed = 1;
		if (chunk.freeable)
			free_pointer(&g_chunks, chunk);
	}
	else
		write(1, "Pointer not found\n", 18);
}

void					*realloc2(void *ptr, size_t size)
{
	t_chunk_find	chunk;

	if (get_chunk(&chunk, &g_chunks, ptr) != NULL)
		return (realloc_chunk(&g_chunks, chunk, ptr, size));
	else
		write(1, "Pointer not found\n", 18);
	return (NULL);
}

void					show_alloc_mem(void)
{
	
}
