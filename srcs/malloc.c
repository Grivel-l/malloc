#include "malloc.h"

static t_chunk_types	chunks = {NULL, NULL, NULL};

void					*malloc(size_t size)
{
	t_chunk	*chunk;

	if ((chunk = init_chunks(&chunks, size)) == NULL)
		return (NULL);
	return (chunk->data);
}
