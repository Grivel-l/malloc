/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 15:44:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 08:43:46 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "malloc.h"

int		main(void)
{
	char	*str;
	/*str = malloc(1);
	str = str - 1 - sizeof(t_chunk);
	((t_chunk *)str)->next = ((t_chunk *)str) + sizeof(t_chunk) + 1;
	((t_chunk *)str)->next->next = ((t_chunk *)str)->next + sizeof(t_chunk) + 1;
	printf("HelloWorld\n");
	return (0);*/
	str = malloc(135);
	memset(str, 'A', 134);
	str[134] = '\0';
	free(str);

	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);

	str = malloc(1136);
	memset(str, 'C', 1135);
	str[1135] = '\0';

	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);

	return (0);
}
