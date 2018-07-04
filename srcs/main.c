/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/17 23:31:46 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/04 15:26:03 by legrivel    ###    #+. /#+    ###.fr     */
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

void					*realloc(void *ptr, size_t size)
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
	/*printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	printf("Size: %zu\n", g_chunks.tiny->size);
	g_chunks.tiny = g_chunks.tiny->next;
	if (g_chunks.tiny == NULL)
		return ;
	return ;*/
	t_chunk_types	chunks;

	chunks.tiny = g_chunks.tiny;
	chunks.small = g_chunks.small;
	chunks.large = g_chunks.large;
	while (1)
	{
		print_alloc_mem(&chunks);
		/*chunks.tiny = chunks.tiny == NULL ? NULL : chunks.tiny->next;
		chunks.small = chunks.small == NULL ? NULL : chunks.small->next;
		chunks.large = chunks.large == NULL ? NULL : chunks.large->next;*/
		if (chunks.tiny == NULL && chunks.small == NULL && chunks.large == NULL)
			break ;
	}
}
