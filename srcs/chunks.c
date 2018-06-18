#include "malloc.h"

static size_t	get_chunk_size(size_t size)
{
	size_t	page_size;
	size_t	total_size;

	size += sizeof(t_chunk);
	page_size = getpagesize();
	total_size = page_size;
	while (total_size < size)
		total_size += page_size;
	return (total_size / page_size);
}

static t_chunk	*create_chunk(t_chunk *chunk, size_t size, size_t type)
{
	size_t	total_size;

	if (type == TINY)
		total_size = getpagesize();
	else if (type != TINY && type != LARGE)
		total_size = getpagesize() * 8;
	else
		total_size = get_chunk_size(size);
	if ((chunk = mmap(NULL, total_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	chunk->next = NULL;
	chunk->size = size;
	chunk->freed = 0;
	return (chunk);
}

static t_chunk	*get_last_chunk(t_chunk *chunk, size_t size, size_t type)
{
	size_t	limit;
	size_t	total_size;

	total_size = 0;
	if (type == TINY)
		limit = getpagesize();
	else if (type != TINY && type != LARGE)
		limit = getpagesize() * 8;
	else
		limit = 0;
	while (chunk->next != NULL)
	{
		total_size += chunk->size + sizeof(t_chunk);
		chunk = chunk->next;
	}
	if (limit == 0 || total_size + size + sizeof(t_chunk) >= limit)
		return (create_chunk(chunk, size, type));
	chunk->next = chunk + sizeof(t_chunk) + chunk->size + 1;
	chunk->next->next = NULL;
	chunk->next->size = size;
	chunk->next->freed = 0;
	return (chunk->next);
}

t_chunk			*init_chunks(t_chunk_types *chunks, size_t size)
{
	if (size <= TINY && chunks->tiny == NULL)
		return (create_chunk(chunks->tiny, size, TINY));
	else if (size <= TINY && chunks->tiny != NULL)
		return (get_last_chunk(chunks->tiny, size, TINY));
	else if (size > TINY && size < LARGE && chunks->small == NULL)
		return (create_chunk(chunks->small, size, 0));
	else if (size > TINY && size < LARGE && chunks->small != NULL)
		return (get_last_chunk(chunks->small, size, 0));
	else
		return (create_chunk(chunks->large, size, LARGE));
}
