/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/13 00:47:41 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/13 00:47:44 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static int	check(void *ptr)
{
	t_chunk	*chunk;

	chunk = g_chunks[0];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	chunk = g_chunks[1];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	chunk = g_chunks[2];
	while (chunk != NULL)
	{
		if (chunk == ptr - sizeof(t_chunk))
			return (0);
		chunk = chunk->next;
	}
	return (1);
}

t_chunk		*get_previous(t_chunk *chunk)
{
	t_chunk *tmp;

	tmp = g_chunks[2];
	while (tmp->next != chunk)
	{
		tmp = tmp->next;
		if (tmp == NULL)
			return (NULL);
	}
	return (tmp);
}

static void	*realloc_big(size_t size, t_chunk *chunk, t_chunk *base, void *ptr)
{
	if (size + sizeof(t_chunk) <= align(base->size, getpagesize()) &&
			base->size < size)
	{
		base->size = size;
		return (ptr);
	}
	else
	{
		chunk = malloc(size);
		ft_memcpy(chunk, ptr, base->size > size ? size : base->size);
		free(ptr);
		return (chunk);
	}
}

size_t		is_fitting(t_chunk *chunk, t_chunk *base, size_t size)
{
	return (((void *)chunk) - ((void *)base) + size + sizeof(t_chunk) <=
			align(base->size, getpagesize()) &&
			(chunk->next == NULL || chunk->next >
			((void *)chunk) + size + sizeof(t_chunk)) &&
			get_type(chunk->size) == get_type(size));
}

void		*realloc(void *ptr, size_t size)
{
	t_chunk *base;
	t_chunk *chunk;

	size = align(size, 16);
	if (ptr == NULL)
		return (malloc(size));
	if (check(ptr))
		return (NULL);
	if (size == 0 && ptr != NULL)
	{
		free(ptr);
		return (malloc(size));
	}
	chunk = ptr - sizeof(t_chunk);
	base = get_base_chunk(chunk, get_type(chunk->size));
	if (get_type(base->size) == -1)
		return (realloc_big(size, chunk, base, ptr));
	if (is_fitting(chunk, base, size) && (chunk->size = size))
		return (ptr);
	if ((base = malloc(size)) == NULL)
		return (NULL);
	ft_memcpy(base, ptr, chunk->size > size ? size : chunk->size);
	free(ptr);
	return (base);
}
