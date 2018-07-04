#include "malloc.h"

static size_t	get_chunk_size(size_t size, size_t type)
{
	size_t	page_size;
	size_t	total_size;

	page_size = getpagesize();
	if (type == TINY)
		return (page_size * TINY_M);
	else if (type == 0)
		return (page_size * SMALL_M);
	size += sizeof(t_chunk);
	total_size = page_size;
	while (total_size < size)
		total_size += page_size;
	return (total_size);
}

static t_chunk	*create_chunk(t_chunk **chunk, size_t size, size_t type)
{
	size_t	chunk_size;

	dprintf(1, "Mmaping...\n");
	chunk_size = get_chunk_size(size, type);
	if ((*chunk = mmap(NULL, chunk_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	(*chunk)->next = NULL;
	(*chunk)->size = size;
	(*chunk)->chunk_size = chunk_size;
	(*chunk)->freed = 0;
	return (*chunk);
}

static t_chunk	*get_last_chunk(t_chunk **chunk, size_t size, size_t type)
{
	size_t	limit;
	size_t	total_size;
	t_chunk	*pointer;
	t_chunk	*tmp;
	void	*yo;

	pointer = *chunk;
	while (*chunk != NULL)
	{
		if (type != LARGE)
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
				if ((tmp = get_last_chunk(chunk, size, type)) == NULL)
					return (NULL);
				*chunk = pointer;
				return (tmp);
			}
		}
		tmp = *chunk;
		*chunk = (*chunk)->next;
	}
	if ((tmp->next = create_chunk(chunk, size, type)) == NULL)
		return (NULL);
	if (pointer != NULL)
		*chunk = pointer;
	return (tmp->next);
}

t_chunk			*init_chunks(t_chunk_types *chunks, size_t size)
{
	if (size <= TINY && chunks->tiny == NULL)
		return (create_chunk(&(chunks->tiny), size, TINY));
	else if (size <= TINY && chunks->tiny != NULL)
		return (get_last_chunk(&(chunks->tiny), size, TINY));
	else if (size > TINY && size < LARGE && chunks->small == NULL)
		return (create_chunk(&(chunks->small), size, 0));
	else if (size > TINY && size < LARGE && chunks->small != NULL)
		return (get_last_chunk(&(chunks->small), size, 0));
	else
		return (get_last_chunk(&(chunks->large), size, LARGE));
}
