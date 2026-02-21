#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("getcwd(): %s\ngetenv(): %s\n", cwd, getenv("PWD"));
	free(cwd);
	return (0);
}
