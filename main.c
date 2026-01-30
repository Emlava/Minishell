/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:35 by elara-va          #+#    #+#             */
/*   Updated: 2026/01/30 18:03:57 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*prompt;
	char	*usr_command;
	pid_t	child_process;
	char	*absolute_path;
	char	*argv[2];

	(void)ac;
	(void)av;
	printf("This initial version of Minishell will display a prompt and is only capable of handling the ls command.\n\n");
	prompt = "42_minishell: ";
	usr_command = readline(prompt);
	if (ft_strncmp("ls", usr_command, 3) != 0)
		printf("The command entered by the user was not ls.\n");
	else
	{
		argv[0] = usr_command;
		argv[1] = NULL;
		absolute_path = ft_strjoin("/usr/bin", usr_command);
		child_process = fork();
		if (child_process == 0)
			execve("/usr/bin/ls", argv, envp);
		free(absolute_path);
	}
	wait(NULL);
	printf("\nThanks for using this simple shell. Bye!\n\n");
	free(usr_command);
	return (0);
}
