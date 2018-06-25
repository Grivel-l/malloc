/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 15:44:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 01:12:27 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "malloc.h"

int		main(void)
{
	char	*str;
	char	*str2;
	/*str = malloc(1);
	str = str - 1 - sizeof(t_chunk);
	((t_chunk *)str)->next = ((t_chunk *)str) + sizeof(t_chunk) + 1;
	((t_chunk *)str)->next->next = ((t_chunk *)str)->next + sizeof(t_chunk) + 1;
	printf("HelloWorld\n");
	return (0);*/
	str2 = malloc(135);
	memset(str2, 'A', 134);
	str2[134] = '\0';

	/*str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);*/

	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	printf("Hey\n");
	free(str2);

	/*str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);*/

	return (0);
}
