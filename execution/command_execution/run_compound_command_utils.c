/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_compound_command_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:36:44 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 16:30:52 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_commands(t_cmd *command_list)
{
	int	command_count;

	command_count = 0;
	while (command_list != NULL)
	{
		command_count++;
		command_list = command_list->next;
	}
	return (command_count);
}

void	close_unused_fds(t_pipes *pipe_list)
{
	while (pipe_list)
	{
		close(pipe_list->pipe[0]);
		close(pipe_list->pipe[1]);
		pipe_list = pipe_list->next;
	}
	return ;
}

// Returns the exit status of the last child process.
int	wait_for_all_children(t_pids *pid_list)
{
	int	wstatus;

	while (pid_list != NULL && pid_list->pid != -1)
	{
		waitpid(pid_list->pid, &wstatus, 0);
		pid_list = pid_list->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
	{
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT)
				write(2, "\n", 1);
			else if (WTERMSIG(wstatus) == SIGQUIT)
			{
				if (WCOREDUMP(wstatus))
					ft_dprintf(2, "Quit (core dumped)\n");
				else
					ft_dprintf(2, "Quit\n");
			}
		}
		return (WTERMSIG(wstatus) + 128);
	}
}

void	exit_dup2_failure(t_subshell_resources *subshell_resources,
	t_exec_resources *res, t_prompt_resources *prompt)
{
	free_pipe_list(subshell_resources->pipe_list);
	free_pid_list(subshell_resources->pid_list);
	exit_cleanup(res, prompt);
	ft_dprintf(2, "minishell: dup2() failure\n");
	exit(EXIT_FAILURE);
}
