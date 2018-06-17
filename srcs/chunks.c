#include "malloc.h"

size_t	get_chunk_size(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();
	return ((sizeof(t_chunk) + size) < page_size ? ((sizeof(t_chunk) + size) / page_size) + 1 : (sizeof(t_chunk) + size)) / page_size);
}

void	*create_chunk(t_chunk *chunk, size_t size)
{
	int		fd;
	void	*pointer;

	if ((fd = open("/dev/zero", O_RDWR)) == -1)
		return (NULL);
	if ((pointer = mmap(NULL, get_chunk_size(size),
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILEED)
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	return (pointer);
}

void	*init_chunks(t_chunk_types *chunks, size_t size)
{
	if (size <= TINY && chunks->tiny == NULL)
		return (create_chunk(chunks->tiny, size));
	else if (size <= TINY && chunks->tiny != NULL)
		return (chunks->tiny);
	else if (size >= SMALL && size < LARGE && chunks->small == NULL)
		return (create_chunk(chunks->small, size));
	else if (size >= SMALL && size < LARGE && chunks->small != NULL)
		return (chunks->small);
	else
		return (create_chunk(chunks->large, size));
}
