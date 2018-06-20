/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/17 23:31:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 08:45:48 by legrivel    ###    #+. /#+    ###.fr     */
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
	return (chunk + sizeof(t_chunk));
}

void					free(void *ptr)
{
	t_chunk	*chunk;
	t_chunk	*previous;

	previous = NULL;
	if ((chunk = get_chunk(g_chunks, &previous, ptr)) != NULL)
	{
		if (previous != NULL)
			previous->next = chunk->next;
		chunk->freed = 1;
		if (munmap(chunk, chunk->size + sizeof(t_chunk)) == -1)
			printf("Error: %s\n", strerror(errno));
	}
	else
		write(1, "Pointer\n", 8);
}
