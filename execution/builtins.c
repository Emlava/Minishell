/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/20 19:18:21 by elara-va         ###   ########.fr       */
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

int	manage_builtin(t_cmd *command, int curr_exit_status, char **local_envp, char **prompt)
{
	if (command->is_builtin == 1)
		return (ft_echo(command->argv));
	if (command->is_builtin == 2)
		return (ft_cd(command->argv, prompt));
	if (command->is_builtin == 3)
		return (ft_pwd(command->argv));
	if (command->is_builtin == 4)
		return (ft_export(command->argv));
	if (command->is_builtin == 5)
		return (ft_unset(command->argv));
	if (command->is_builtin == 6)
		return (ft_env(command->argv));
}

// Things to free or close:
// ft_cd():
// 	-err_str
// 	-dirp (close)
// ft_pdw():
// 	-working_dir
