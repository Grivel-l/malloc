/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 15:44:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/02 15:02:38 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	str2 = malloc(135);
	memset(str2, 'A', 134);
	str2[134] = '\0';

	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);

	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	str = realloc(str, 131);
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	str = realloc(str, 131);
	free(str);
	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	str = realloc(str, 161);
	free(str);
	str3 = malloc(100);
	memset(str3, 'B', 99);
	str3[99] = '\0';
	str3 = realloc(str3, 101);
	str4 = malloc(100);
	memset(str4, 'B', 99);
	str4[99] = '\0';
	str4 = realloc(str4, 101);
	free(str3);
	free(str4);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	str = realloc(str, 160);
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(130);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	str = malloc(100);
	memset(str, 'B', 99);
	str[99] = '\0';
	free(str);
	str = malloc(4000);
	memset(str, 'C', 129);
	str[129] = '\0';
	free(str);
	free(str2);
	str = malloc(0);
	free(str);

	str = malloc(10);
	memset(str, 'A', 10);
	str[9] = '\0';
	printf("This one: %s\n", str);
	str = realloc(str, 15);
	memset(str + 9, 'B', 5);
	str[14] = '\0';
	printf("This one: %s\n", str);
 	free(str);

	str = malloc(120);
	memset(str, 'A', 120);
	str = realloc(str, 121);
	// str[119] = 'B';
	str[120] = '\0';
	free(str);

	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);
	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);
	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);
	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);
	str = malloc(131072);
	memset(str, 'D', 131071);
	str[131071] = '\0';
	free(str);
	return (0);
}
