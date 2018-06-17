#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <errno.h>

// void		free(void *ptr);
// void		show_alloc_mem(void);
void		*malloc(size_t size);
// void		*realloc(void *ptr, size_t size);

# define TINY 64
# define TINY_S 4
# define SMALL 512
# define SMALL_S 32
# define LARGE 131072

typedef struct		s_chunk
{
	struct s_chunk	*previous;
	struct s_chunk	*next;
	size_t			size;
	size_t			freed;
	size_t			total_size;
	void			*data;
}					t_chunk;

typedef struct		s_chunk_types
{
	t_chunk			*tiny;
	t_chunk			*small;
	t_chunk			*large;
}					t_chunk_types;

t_chunk				*init_chunks(t_chunk_types *chunks, size_t size);

#endif
