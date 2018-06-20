/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/17 23:31:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 05:31:14 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/resource.h>

static t_chunk_types	g_chunks = {NULL, NULL, NULL};

void					*malloc(size_t size)
{
	t_chunk	*chunk;

	if ((chunk = init_chunks(&g_chunks, size)) == NULL)
		return (NULL);
	// printf("First pointer: %p, %p\n", g_chunks.tiny, chunk);
// 	printf("All pointers: %p, %p, %p, %p\n", g_chunks.tiny + sizeof(t_chunk), g_chunks.tiny + sizeof(t_chunk) * 2 + 100, g_chunks.tiny + sizeof(t_chunk) * 3 + 200, g_chunks.tiny + sizeof(t_chunk) * 4 + 300);
	return (chunk + sizeof(t_chunk));
}
