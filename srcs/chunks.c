#include "malloc.h"
#include <string.h>

static size_t	get_chunk_size(size_t size)
{
	size_t	page_size;
	size_t	total_size;

	size += sizeof(t_chunk);
	page_size = getpagesize();
	total_size = page_size;
	while (total_size < size)
		total_size += page_size;
	return (total_size);
}

static t_chunk	*create_chunk(t_chunk **chunk, size_t size)
{
	if ((*chunk = mmap(NULL, get_chunk_size(size),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	(*chunk)->next = NULL;
	(*chunk)->size = size;
	(*chunk)->freed = 0;
	return (*chunk);
}

static t_chunk	*get_last_chunk(t_chunk **chunk, size_t size, size_t type)
{
	size_t	limit;
	size_t	total_size;
	t_chunk	*pointer;
	t_chunk	*next;
	char	*yo;

	pointer = *chunk;
	total_size = 0;
	if (type == TINY)
		limit = getpagesize() * TINY_M;
	else if (type != TINY && type != LARGE)
		limit = getpagesize() * LARGE_M;
	else
		limit = 0;
	while (*chunk != NULL && (*chunk)->next != NULL)
	{
		if (limit != 0)
			total_size += (*chunk)->size + sizeof(t_chunk);
		*chunk = (*chunk)->next;
	}
	if (limit == 0 || total_size + size + sizeof(t_chunk) > limit)
	{
		if (create_chunk(*chunk == NULL ? chunk : &((*chunk)->next), size) == NULL)
			return (NULL);
		next = (*chunk)->next;
		if (pointer != NULL)
			*chunk = pointer;
		return (pointer == NULL ? *chunk : next);
	}
	yo = (char *)*chunk;
	yo = yo + sizeof(t_chunk) + (*chunk)->size;
	(*chunk)->next = (t_chunk *)yo;
	next = (*chunk)->next;
	*chunk = pointer;
	next->freed = 0;
	next->size = size;
	next->next = NULL;
	return (next);
}

t_chunk			*init_chunks(t_chunk_types *chunks, size_t size)
{
	if (size <= TINY && chunks->tiny == NULL)
		return (create_chunk(&(chunks->tiny), size));
	else if (size <= TINY && chunks->tiny != NULL)
		return (get_last_chunk(&(chunks->tiny), size, TINY));
	else if (size > TINY && size < LARGE && chunks->small == NULL)
		return (create_chunk(&(chunks->small), size));
	else if (size > TINY && size < LARGE && chunks->small != NULL)
		return (get_last_chunk(&(chunks->small), size, 0));
	else
		return (get_last_chunk(&(chunks->large), size, LARGE));
}
