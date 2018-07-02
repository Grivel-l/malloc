#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

void		free2(void *ptr);
void		show_alloc_mem(void);
void		*malloc2(size_t size);
void		*realloc2(void *ptr, size_t size);

# define TINY 128
# define TINY_M 1
# define LARGE 131072
# define SMALL_M 8

typedef struct		s_chunk
{
	struct s_chunk	*next;
	size_t			size;
	size_t			freed;
	size_t			chunk_size;
}					t_chunk;

typedef struct		s_chunk_types
{
	t_chunk			*tiny;
	t_chunk			*small;
	t_chunk			*large;
}					t_chunk_types;

typedef struct		s_chunk_find
{
	t_chunk			*next;
	t_chunk			*chunk;
	t_chunk			*previous;
	size_t			freeable;
}					t_chunk_find;

t_chunk				*init_chunks(t_chunk_types *chunks, size_t size);
void				free_pointer(t_chunk_types *chunks, t_chunk_find chunk);
void				*realloc_chunk(t_chunk_types *chunks,
								t_chunk_find chunk, void *ptr, size_t size);
t_chunk_find		*get_chunk(t_chunk_find *chunk, t_chunk_types *chunks, void *ptr);

#endif
