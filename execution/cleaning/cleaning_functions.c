/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:55:30 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 16:02:33 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_exp_vars(t_new_exports *new_exports)
{
	t_new_exports	*tmp;

	while (new_exports)
	{
		tmp = new_exports;
		free(new_exports->var);
		new_exports = new_exports->next;
		free(tmp);
	}
	return ;
}

void	free_pipe_list(t_pipes *pipe_list)
{
	t_pipes	*tmp;

	while (pipe_list)
	{
		tmp = pipe_list;
		pipe_list = pipe_list->next;
		free(tmp);
	}
	return ;
}

void	free_pid_list(t_pids *pid_list)
{
	t_pids	*tmp;

	while (pid_list)
	{
		tmp = pid_list;
		pid_list = pid_list->next;
		free(tmp);
	}
	return ;
}

void	exit_cleanup(t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	free_cmds(exec_resources->command_list);
	ft_free_str_arr(exec_resources->local_envp);
	free_exp_vars(exec_resources->new_exports);
	if (exec_resources->internal_pwd != NULL)
		free(exec_resources->internal_pwd);
	if (exec_resources->prompt != NULL)
		free(exec_resources->prompt);
	if (prompt_resources->free_permanent_substr == true)
		free(prompt_resources->permanent_prompt_substr);
	rl_clear_history();
	return ;
}
