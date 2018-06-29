/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/26 01:54:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/01 23:10:33 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	char	*str;
	char	*copy;
	t_list	*link;

	str = NULL;
	if ((link = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL && (str = malloc(content_size + 1)) == NULL)
	{
		free(link);
		return (NULL);
	}
	link->next = NULL;
	link->content = str;
	link->content_size = content_size;
	if (content != NULL)
	{
		copy = (char *)content;
		while (*copy)
			*str++ = *copy++;
		*str = '\0';
	}
	return (link);
}
