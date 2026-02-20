/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/20 12:08:26 by elara-va         ###   ########.fr       */
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

int	ft_cd(char **argv, char **prompt)
{
	char	*err_str;

	if (argv[2] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", argv[1]); // free
		perror(err_str);
		free(err_str);
		return (2);
	}
	define_prompt(prompt);
	return (0);
}

int	ft_pwd(char **argv)
{
	char	*working_dir;

	if (argv[1] != NULL && argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: pwd: no options for this builtin\n");
		return (1);
	}
	working_dir = getcwd(NULL, 0); // free
	if (working_dir == NULL)
		return (2);
	printf("%s\n", working_dir);
	free(working_dir);
	return (0);
}

// int	ft_export(char **argv)
// {
// 	int		i;
// 	char	*err_str;

// 	if (argv[1] == NULL)
// 	{
// 		// Print all exported variables
// 		return (0);
// 	}
// 	if (argv[1][0] == '-')
// 	{
// 		ft_dprintf(2, "minishell: export: no options for this builtin\n");
// 		return (1);
// 	}
// 	i = 1;
// 	while (argv[i] != NULL)
// 	{
		
// 	}
// }

int	manage_builtin(char **argv, int prev_exit_status, char **prompt)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (ft_echo(argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (ft_cd(argv, prompt));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (ft_pwd(argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (ft_export(argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (ft_unset(argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (ft_env(argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0) // Put this where the commented * is in the main
	{
		// print error before exiting if argv[1] != NULL, but return 1
		// clean_up(things to free or close);
		printf("exit\n"); // Make sure this goes to the terminal
		// if redirections were implemented
		exit(prev_exit_status);
	}
}

// Things to free or close:
// ft_cd():
// 	-err_str
// 	-dirp (close)
// ft_pdw():
// 	-working_dir
