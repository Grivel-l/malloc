#include <errno.h>
#include <string.h>
#include "malloc.h"

int		main(void)
{
	char	*yo;

	if ((yo = malloc(3)) == NULL)
	{
		printf("Error: %s\n", strerror(errno));
		return (1);
	}
	yo[0] = 'y';
	yo[1] = 'o';
	yo[2] = '\n';
	write(1, yo, 3);
	printf("Hey: |%s|\n", yo);
	return (0);
}
