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

static void	print_address(void *address)
{
	size_t	nbr;
	size_t	tmp;
	char	*result;
	void	*pointer;

	if ((result = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return ;
	pointer = result;
	write(1, "0x", 2);
	nbr = (size_t)address;
	while (nbr != 0)
	{
		tmp = nbr % 16;
		if (tmp <= 9)
			*result = tmp + 48;
		else
			*result = 97 + tmp - 10;
		result += 1;
		nbr /= 16;
	}
	while ((void *)result >= pointer)
	{
		write(1, &(*result), 1);
		result -= 1;
	}
	munmap(pointer, getpagesize());
}

void		print_chunk(t_chunk *chunk)
{
	print_address(((void *)chunk) + sizeof(t_chunk));
	write(1, " - ", 3);
	print_address(((void *)chunk) + sizeof(t_chunk) + chunk->size);
	write(1, " : ", 3);
	ft_putnbr(chunk->size);
	write(1, " bytes\n", 7);
}

void		print_chunks(t_chunk **chunk, int type)
{
	int	total;
	int	pagesize;

	if ((*chunk)->freed)
	{
		*chunk = (*chunk)->next;
		return ;
	}
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
		if (*chunk == NULL ||
	total + (*chunk)->size + sizeof(t_chunk) > (size_t)(pagesize * type))
			return ;
	}
}

void		print_alloc_mem(t_chunk *chunks0,
t_chunk *chunks1, t_chunk *chunks2)
{
	if (chunks0 == NULL && chunks1 == NULL && chunks2 == NULL)
		return ;
	if (chunks0 != NULL && (chunks1 == NULL || chunks0 < chunks1) &&
		(chunks2 == NULL || chunks0 < chunks2))
		print_chunks(&chunks0, TINY);
	if (chunks1 != NULL && (chunks0 == NULL || chunks1 < chunks0) &&
		(chunks2 == NULL || chunks1 < chunks2))
		print_chunks(&chunks1, SMALL);
	if (chunks2 != NULL && (chunks1 == NULL || chunks2 < chunks1) &&
		(chunks0 == NULL || chunks2 < chunks0))
		print_chunks(&chunks2, -1);
	print_alloc_mem(chunks0, chunks1, chunks2);
}

void		show_alloc_mem(void)
{
	print_alloc_mem(g_chunks[0], g_chunks[1], g_chunks[2]);
}
