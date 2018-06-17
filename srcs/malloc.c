#include "malloc.h"

static t_chunk_types	chunks;

void					*malloc(size_t size)
{
	t_chunk	*chunk;

	if ((chunk = init_chunks(&chunks, size)) == NULL)
		return (NULL);
	if ((fd = open("/dev/zero", O_RDWR)) == -1)
		return (NULL);
	if ((ptr =
mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
