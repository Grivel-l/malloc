/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/02 15:26:51 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/04 15:42:50 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void		print_address(void *address)
{
	dprintf(1, "%p", address);
}

void    print_chunk(t_chunk *chunk)
{
    print_address(((void *)chunk) + sizeof(t_chunk));
    write(1, " - ", 3);
    print_address(((void *)chunk) + sizeof(t_chunk) + chunk->size);
    write(1, " : ", 3);
    ft_putnbr(chunk->size);
    write(1, " bytes\n", 7);
}

void    print_chunks(t_chunk **chunk, int type)
{
    int     total;
    int     pagesize;

    if (type == TINY)
      write(1, "TINY : ", 7);
    else if (type == SMALL)
      write(1, "SMALL : ", 8);
    else
      write(1, "LARGE : ", 8);
    print_address(((void *)*chunk) + sizeof(t_chunk));
    write(1, "\n", 1);
    if (type == -1)
    {
      print_chunk(*chunk);
      *chunk = (*chunk)->next;
      return ;
    }
    total = 0;
    pagesize = getpagesize();
    while (total < pagesize * type)
    {
      print_chunk(*chunk);
      total += (*chunk)->size + sizeof(t_chunk);
      *chunk = (*chunk)->next;
      if (*chunk == NULL || total + (*chunk)->size + sizeof(t_chunk) > (size_t)(pagesize * type))
        return ;
    }
}

void			print_alloc_mem(t_chunk *chunks[3])
{
    if (chunks[0] == NULL && chunks[1] == NULL && chunks[2] == NULL)
      return ;
    if (chunks[0] != NULL && (chunks[1] == NULL || chunks[0] < chunks[1]) && (chunks[2] == NULL || chunks[0] < chunks[2]))
      print_chunks(&(chunks[0]), TINY);
    if (chunks[1] != NULL && (chunks[0] == NULL || chunks[1] < chunks[0]) && (chunks[2] == NULL || chunks[1] < chunks[2]))
      print_chunks(&(chunks[1]), SMALL);
    if (chunks[2] != NULL && (chunks[1] == NULL || chunks[2] < chunks[1]) && (chunks[0] == NULL || chunks[2] < chunks[0]))
      print_chunks(&(chunks[2]), -1);
    print_alloc_mem(chunks);
}
