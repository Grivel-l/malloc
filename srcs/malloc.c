#include "malloc.h"

static size_t	get_chunk_size(size_t size, size_t type, size_t page_size)
{
	size_t	total_size;

	if (type == TINY_M || type == SMALL_M)
		return (page_size * type);
	size += sizeof(t_chunk);
	total_size = page_size;
	while (total_size < size)
		total_size += page_size;
	return (total_size);
}

static t_chunk	*create_chunk(t_chunk **chunk, size_t size, size_t type, size_t page_size)
{
	size_t	chunk_size;

	chunk_size = get_chunk_size(size, type, page_size);
	if ((*chunk = mmap(NULL, chunk_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	(*chunk)->next = NULL;
	(*chunk)->size = size;
	(*chunk)->chunk_size = chunk_size;
	(*chunk)->freed = 0;
	return (*chunk);
}

static t_chunk	*get_last_chunk(t_chunk **chunk, size_t size, size_t type, size_t page_size)
{
	size_t	limit;
	size_t	total_size;
	t_chunk	*pointer;
	t_chunk	*tmp;
	void	*yo;

	pointer = *chunk;
	while (*chunk != NULL)
	{
		if (type != 0)
		{
			if ((*chunk)->chunk_size != 0)
			{
				total_size = 0;
				limit = (*chunk)->chunk_size;
			}
			total_size += (*chunk)->size + sizeof(t_chunk);
			if ((*chunk)->next == NULL)
			{
				if (total_size + size + sizeof(t_chunk) <= limit)
				{
					yo = (void *)*chunk;
					yo = yo + sizeof(t_chunk) + (*chunk)->size;
					(*chunk)->next = (t_chunk *)yo;
					tmp = (*chunk)->next;
					*chunk = pointer;
					tmp->freed = 0;
					tmp->size = size;
					tmp->next = NULL;
					tmp->chunk_size = 0;
					return (tmp);
				}
			}
			else if ((*chunk)->next != NULL && (*chunk)->next->chunk_size != 0)
			{
				*chunk = (*chunk)->next;
				if ((tmp = get_last_chunk(chunk, size, type, page_size)) == NULL)
					return (NULL);
				*chunk = pointer;
				return (tmp);
			}
		}
		tmp = *chunk;
		*chunk = (*chunk)->next;
	}
	if (pointer == NULL && (tmp = create_chunk(chunk, size, type, page_size)) == NULL)
		return (NULL);
	else if (pointer != NULL && (tmp->next = create_chunk(chunk, size, type, page_size)) == NULL)
		return (NULL);
	if (pointer != NULL)
		*chunk = pointer;
	return (pointer == NULL ? tmp : tmp->next);
}

t_chunk			*init_chunks(t_chunk_types *chunks, size_t size)
{
	size_t	tiny;
	size_t	large;
	size_t	page_size;

	page_size = getpagesize();
	tiny = page_size * TINY_M / DIVIDER;
	large = page_size * SMALL_M / DIVIDER;
	if (size <= tiny && chunks->tiny == NULL)
		return (create_chunk(&(chunks->tiny), size, TINY_M, page_size));
	else if (size <= tiny && chunks->tiny != NULL)
		return (get_last_chunk(&(chunks->tiny), size, TINY_M, page_size));
	else if (size > tiny && size <= large && chunks->small == NULL)
		return (create_chunk(&(chunks->small), size, SMALL_M, page_size));
	else if (size > tiny && size <= large && chunks->small != NULL)
		return (get_last_chunk(&(chunks->small), size, SMALL_M, page_size));
	else
		return (get_last_chunk(&(chunks->large), size, 0, page_size));
}
