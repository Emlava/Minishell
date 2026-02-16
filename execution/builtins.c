/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/16 21:02:17 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **argv)
{
	int		i;
	bool	n_option;

	i = 1;
	if (ft_strncmp(argv[1], "-n", 3) == 0)
	{
		i++;
		n_option = true;
	}
	else
		n_option = false;
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n_option == false)
		write(1, "\n", 1);
	return (0);
}

int	manage_builtin(char **argv, int prev_exit_status)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (ft_echo(argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (ft_cd(argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (ft_pwd(argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (ft_export(argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (ft_unset(argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (ft_env(argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
	{
		// clean_up(things to free or close);
		printf("exit\n"); // Make sure this goes to the terminal
		// if redirections were implemented
		exit(prev_exit_status);
	}
}
