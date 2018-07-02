/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/02 15:26:51 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/02 19:14:30 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static void		print_address(void *address)
{
	dprintf(1, "%p", address);
}

static size_t	print_chunk(t_chunk **chunk, size_t type)
{
	void			*pointer;
	static size_t	old_type = -1;

	pointer = (void *)(*chunk);
	if (old_type != type)
	{
		old_type = type;
		if (type == TINY)
			ft_putstr("TINY : ");
		else if (type == 0)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		print_address(pointer);
		ft_putchar('\n');
	}
	if ((*chunk)->next == NULL || (*chunk)->next != NULL && (*chunk)->next->chunk_size != 0)
		old_type = -1;
	print_address(pointer + sizeof(t_chunk));
	ft_putstr(" - ");
	print_address(pointer + sizeof(t_chunk) + (*chunk)->size);
	ft_putstr(" : ");
	ft_putnbr((*chunk)->size);
	ft_putstr((*chunk)->size > 1 ? " octets\n" : " octet\n");
	*chunk = (*chunk)->next;
	return (1);
}

static size_t	print_asc(t_chunk **chunk, t_chunk **chunk2, t_chunk **chunk3, size_t type)
{
	if (*chunk != NULL)
	{
		if (*chunk2 == NULL && *chunk3 == NULL)
			return (print_chunk(chunk, type));
		else if (*chunk2 != NULL)
		{
			if (*chunk3 != NULL)
			{
				if (*chunk < *chunk2 && *chunk < *chunk3)
					return (print_chunk(chunk, type));
			}
			else
				if (*chunk < *chunk2)
					return (print_chunk(chunk, type));
		}
		else
		{
			if (*chunk3 != NULL)
			{
				if (*chunk < *chunk3)
					return (print_chunk(chunk, type));
			}
		}
	}
	return (0);
}

void			print_alloc_mem(t_chunk_types *chunks)
{
	if (print_asc(&(chunks->tiny), &(chunks->small), &(chunks->large), TINY) == 0)
		if (print_asc(&(chunks->small), &(chunks->tiny), &(chunks->large), 0) == 0)
			print_asc(&(chunks->large), &(chunks->small), &(chunks->tiny), LARGE);
}
