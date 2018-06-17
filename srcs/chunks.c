#include "malloc.h"

static size_t	get_chunk_size(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();
	return ((sizeof(t_chunk) + size) < page_size ? ((sizeof(t_chunk) + size) / page_size) + 1 : (sizeof(t_chunk) + size) / page_size);
}

static t_chunk	*create_chunk(t_chunk *chunk, size_t size)
{
	int		fd;
	size_t	total_size;

	if ((fd = open("/dev/zero", O_RDWR)) == -1)
		return (NULL);
	total_size = get_chunk_size(size);
	if ((chunk = mmap(NULL, total_size,
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	chunk->previous = NULL;
	chunk->next = NULL;
	chunk->size = size;
	chunk->freed = 0;
	chunk->data = chunk + sizeof(t_chunk);
	chunk->total_size = total_size * getpagesize();
	return (chunk);
}

static t_chunk	*get_last_chunk(t_chunk *chunk, size_t size)
{
	size_t	limit;
	size_t	total_size;

	total_size = 0;
	limit = chunk->total_size;
	while (chunk->next != NULL)
	{
		total_size += chunk->size;
		chunk = chunk->next;
	}
	if (total_size + size >= limit)
		return (create_chunk(chunk, size));
	chunk->next = chunk + sizeof(t_chunk) + chunk->size + 1;
	chunk->next->previous = chunk;
	chunk->next->next = NULL;
	chunk->next->size = size;
	chunk->next->freed = 0;
	chunk->next->data = chunk->next + sizeof(t_chunk);
	return (chunk->next);
}

t_chunk			*init_chunks(t_chunk_types *chunks, size_t size)
{
	if (size <= TINY && chunks->tiny == NULL)
		return (create_chunk(chunks->tiny, size));
	else if (size <= TINY && chunks->tiny != NULL)
		return (get_last_chunk(chunks->tiny, size));
	else if (size >= SMALL && size < LARGE && chunks->small == NULL)
		return (create_chunk(chunks->small, size));
	else if (size >= SMALL && size < LARGE && chunks->small != NULL)
		return (get_last_chunk(chunks->small, size));
	else
		return (create_chunk(chunks->large, size));
}
