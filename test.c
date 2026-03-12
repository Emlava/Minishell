#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int	main(void)
{
	char	*str;
	int	pfds[2];
	pid_t	pid;
	int	i;
	int	wstatus;

	if (pipe(pfds) == -1)
		return (1);
	str = malloc(sizeof(char) * 50);
	if (!str)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0) // Child
	{
		printf("This is the child asking you for an input string that will be passed to and printed by the parent.");
		printf("\nEnter your input: ");
		scanf("%s", str);
		i = 0;
		close(pfds[0]);
		do
			write(pfds[1], &str[i], 1);
		while (str[i++]);
		close(pfds[1]);
		free(str);
		return (0);
	}
	// Parent
	close(pfds[1]);
	waitpid(pid, &wstatus, 0);
	i = 0;
	do
		read(pfds[0], &str[i], 1);
	while (str[i++] != '\0');
	close(pfds[0]);
	printf("This is the parent.\nThe child passed a string of %d characters: %s\n", (int)strlen(str), str);
	if (WIFEXITED(wstatus))
		printf("The child exited with status %d.\n", WEXITSTATUS(wstatus));
	free(str);
	return (0);
}
