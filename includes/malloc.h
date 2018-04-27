#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>

void		free(void *ptr);
void		show_alloc_mem(void);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

#endif
