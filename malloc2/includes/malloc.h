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

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "../../libft/libft.h"

# define TINY 1
# define SMALL 8

typedef struct s_chunk
{
    size_t  size;
    void    *next;
    char    freed;
}             t_chunk;

void    *malloc(size_t size);

void    print_alloc_mem(t_chunk *chunks0, t_chunk *chunks1, t_chunk *chunks2);
