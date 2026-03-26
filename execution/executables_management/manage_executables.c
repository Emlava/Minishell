/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_executables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:47:11 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/26 16:11:31 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	run_directly(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	char	*final_path;
	char	*err_str;

	final_path = define_non_reiterative_path(argv[0], exec_resources,
			prompt_resources->home);
	if (final_path == NULL)
	{
		exit_cleanup(exec_resources, prompt_resources);
		exit(1);
	}
	if (execve(final_path, argv, exec_resources->local_envp) == -1)
	{
		err_str = ft_strjoin("minishell: ", argv[0]);
		perror(err_str);
		free(err_str);
		free(final_path);
		exit_cleanup(exec_resources, prompt_resources);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

static void	exit_exec_err(t_exec_resources *res, t_prompt_resources *pres,
	t_pipes *pipe_list, int code)
{
	exit_cleanup(res, pres);
	if (pipe_list != NULL)
		free_pipe_list(pipe_list);
	exit(code);
}

static void	execute_from_path(char **argv, t_exec_resources *res,
	t_prompt_resources *pres, t_pipes *pipes)
{
	int		i;
	char	*pot_path;
	char	*tmp_str;
	char	**p_list;

	p_list = ft_split(get_local_env(res->local_envp, "PATH"), ':');
	if (!p_list)
		exit_exec_err(res, pres, pipes, 2);
	i = -1;
	while (p_list[++i])
	{
		tmp_str = ft_strjoin(p_list[i], "/");
		pot_path = ft_strjoin(tmp_str, argv[0]);
		free(tmp_str);
		if (pot_path == NULL)
			(ft_free_str_arr(p_list), exit_exec_err(res, pres, pipes, 3));
		execve(pot_path, argv, res->local_envp);
		if (p_list[i + 1] == NULL)
		{
			ft_dprintf(2, "minishell: %s: command not found\n", argv[0]);
			(free(pot_path), ft_free_str_arr(p_list));
			exit_exec_err(res, pres, pipes, 127);
		}
		free(pot_path);
	}
}

void	run_executable(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources, t_pipes *pipe_list)
{
	char	*path_env_var;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_memchr(argv[0], '/', ft_strlen(argv[0])) != NULL)
		run_directly(argv, exec_resources, prompt_resources);
	path_env_var = get_local_env(exec_resources->local_envp, "PATH");
	if (!path_env_var)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", argv[0]);
		exit_exec_err(exec_resources, prompt_resources, pipe_list, 127);
	}
	execute_from_path(argv, exec_resources, prompt_resources, pipe_list);
}
