/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:47:11 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/01 01:41:08 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_executable(char **argv, t_exec_resources *exec_resources)
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
		path_env_var = get_local_env(exec_resources->local_envp, "PATH");
		path_list = ft_split(path_env_var, ':'); // free
		if (path_list == NULL)
			exit(1); // We have to free and close everything! Maybe with the builtin cleanup function.
		i = 0;
		while (1)
		{
			tmp_str = ft_strjoin(path_list[i], "/"); // free
			potential_path = ft_strjoin(tmp_str, argv[0]);
			free(tmp_str);
			if (potential_path == NULL)
				exit(2); // We have to free and close everything!
			if (execve(potential_path, argv, exec_resources->local_envp) == -1
				&& path_list[i + 1] == NULL)
			{
				free(potential_path);
				// free and close everything else
				ft_dprintf(2, "minishell: %s: command not found\n", argv[0]);
				exit(errno + 128);
			}
			free(potential_path);
			i++;
		}
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
