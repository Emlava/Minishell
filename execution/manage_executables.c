/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:47:11 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/01 18:39:50 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_directly(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	char	*final_path;
	char	*err_str;

	final_path = define_non_reiterative_path(argv[0], exec_resources,
		prompt_resources->home); // free
	if (final_path == NULL)
	{
		exit_cleanup(exec_resources, prompt_resources);
		exit(1);
	}
	if (execve(final_path, argv, exec_resources->local_envp) == -1)
	{
		err_str = ft_strjoin("minishell: ", argv[0]); // free
		perror(err_str);
		free(err_str);
		free(final_path);
		exit_cleanup(exec_resources, prompt_resources);
		exit(errno + 128);
	}
	return ;
}

int	run_executable(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	pid_t	pid;
	char	*path_env_var;
	char	**path_list;
	int		i;
	char	*potential_path;
	char	*tmp_str;
	int		wstatus;

	pid = fork();
	if (pid == 0)
	{
		if (ft_memchr(argv[0], '/', ft_strlen(argv[0])) != NULL)
			run_directly(argv, exec_resources, prompt_resources);
		// else
		//	look_in_path();
		// All this goes in look_in_path();
		path_env_var = get_local_env(exec_resources->local_envp, "PATH");
		path_list = ft_split(path_env_var, ':'); // free
		if (path_list == NULL)
		{
			exit_cleanup(exec_resources, prompt_resources);
			exit(2);
		}
		i = 0;
		while (1)
		{
			tmp_str = ft_strjoin(path_list[i], "/"); // free
			potential_path = ft_strjoin(tmp_str, argv[0]);
			free(tmp_str);
			if (potential_path == NULL)
			{
				ft_free_str_arr(path_list);
				exit_cleanup(exec_resources, prompt_resources);
				exit(3);
			}
			if (execve(potential_path, argv, exec_resources->local_envp) == -1
				&& path_list[i + 1] == NULL)
			{
				ft_dprintf(2, "minishell: %s: command not found\n", argv[0]);
				ft_free_str_arr(path_list);
				free(potential_path);
				exit_cleanup(exec_resources, prompt_resources);
				exit(errno + 128);
			}
			free(potential_path);
			i++;
		}
		//
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		// Do we check for signal termination?
		// If so:
		// if (WIFSIGNALED(wstatus))
		// 	return (WTERMSIG(wstatus));
		//
		else
			return (0); // Just to silence compilation warnings
		//
	}
}
