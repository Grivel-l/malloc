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

#include "malloc.h"

int		main(void)
{
	char	*str;
	char	*str2;

	dprintf(1, "Sizeof: %zu\n", sizeof(t_chunk));
	str = malloc2(50);
	memset(str, 'D', 49);
	str[49] = '\0';
	dprintf(1, "Str: %p\n", str);
	str2 = malloc2(37);
	memset(str2, 'E', 36);
	str2[36] = '\0';
	dprintf(1, "Str2: %p\n", str2);
	str = realloc2(str, 55);
	dprintf(1, "HelloWorld\n");
	dprintf(1, "Str: %s\n", str);
	memset(str + 49, 'A', 5);
	str[54] = '\0';
	printf("Str: %s\n", str);
 	free2(str);
	free2(str2);
	return (0);
}
