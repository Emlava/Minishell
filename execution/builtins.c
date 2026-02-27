/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/27 17:29:47 by elara-va         ###   ########.fr       */
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

int	ft_cd(char **argv, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	char	*err_str;

	if (strncmp(argv[1], ".", 2) == 0)
		return (0);
	if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	define_non_reiterative_path(argv, exec_resources, prompt_resources->home);
	if (argv[1] == NULL)
	{
		ft_dprintf(2, "minishell: cd: failed to manage path because of a malloc failure\n");
		return (2);
	}
	if (chdir(argv[1]) == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", argv[1]); // free
		if (err_str != NULL)
		{
			perror(err_str);
			free(err_str);
		}
		return (3);
	}
	if (exec_resources->pwd_present == true)
		update_local_env_paths(exec_resources, argv[1]);
	if (exec_resources->prompt != NULL)
		define_prompt(&exec_resources->prompt, prompt_resources, exec_resources->local_envp);
	return (0);
}

int	ft_pwd(char **argv, char **local_envp)
{
	char	*working_dir;

	if (argv[1] != NULL && argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: pwd: no options for this builtin\n");
		return (1);
	}
	working_dir = get_local_env(local_envp, "PWD");
	if (working_dir == NULL)
		return (2);
	printf("%s\n", working_dir);
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

int	ft_exit(char **argv, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	unsigned char	exit_status;

	// if piping was implemented, we manage things differently
	printf("exit\n");
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		if (!ft_is_numeric_str(argv[1]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric arguments required\n", argv[1]);
			exit_status = 2;
		}
		else
			exit_status = (unsigned char)ft_atoi(argv[1]);
	}
	else
		exit_status = exec_resources->curr_exit_status;
	exit_cleanup(exec_resources, prompt_resources);
	exit(exit_status);
}

int	manage_builtin(t_cmd *command, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	if (command->builtin == BUILTIN_ECHO)
		return (ft_echo(command->argv));
	if (command->builtin == BUILTIN_CD)
		return (ft_cd(command->argv, exec_resources, prompt_resources));
	if (command->builtin == BUILTIN_PWD)
		return (ft_pwd(command->argv, exec_resources->local_envp));
	// if (command->builtin == BUILTIN_EXPORT)
	// 	return (ft_export(command->argv));
	// if (command->builtin == BUILTIN_UNSET)
	// 	return (ft_unset(command->argv));
	// if (command->builtin == BUILTIN_ENV)
	// 	return (ft_env(command->argv));
	else
		return (ft_exit(command->argv, exec_resources, prompt_resources));
}

// Things to free or close:
// ft_cd():
// 	-err_str
// 	-dirp (close)
// ft_pdw():
// 	-working_dir
