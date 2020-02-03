/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 18:29:26 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 19:51:13 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define TINY 128
# define SMALL 1024

struct			s_chunk
{
	size_t		size;
	void		*next;
	char		freed;
        int             a;
        int             b;
};

typedef struct s_chunk		t_chunk;

extern t_chunk		*(g_chunks[3]);

void			*malloc(size_t size);

void			free(void *ptr);

int				get_type(size_t size);
t_chunk			*get_base_chunk(t_chunk *chunk, int type);
size_t			get_chunk_size(size_t size, int page_size);
int				check_freed(t_chunk **tmp, size_t total,
				size_t page_freed, size_t chunk_size);

void			print_alloc_mem(t_chunk *chunks0,
t_chunk *chunks1, t_chunk *chunks2);
#endif
