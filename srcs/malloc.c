#include "malloc.h"

void		*malloc(size_t size)
{
	size_t	i;
	int		fd;
	int		*ptr;

	if ((fd = open("./yo", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600)) == -1)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		write(fd, "", 1);
		i += 1;
	}
	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
