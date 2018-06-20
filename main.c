/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 15:44:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 05:42:19 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>
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
	str = malloc(120);
	printf("%p, %p, %p, %p\n", str, str + 120 + 24, str + 48 + 220, str + 72 + 320);
	memset(str, 'A', 99);
	str[99] = '\0';
	printf("Str: %p, %s\n\n", str, str);

	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	printf("Str: %p, %s\n\n", str, str);

	str = malloc(100);
	memset(str, 'C', 99);
	str[99] = '\0';
	printf("Str: %p, %s\n\n", str, str);

	str = malloc(100);
	memset(str, 'D', 99);
	str[99] = '\0';
	printf("Str: %p, %s\n\n", str, str);

	return (0);
}
