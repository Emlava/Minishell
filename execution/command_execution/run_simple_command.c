/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:10:45 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 12:08:33 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_simple_command(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	t_cmd	*command_node;
	pid_t	pid;
	int		wstatus;

	command_node = exec_resources->command_list;
	if (command_node->builtin)
		exec_resources->curr_exit_status = manage_builtin(command_node, exec_resources, prompt_resources);	
	if (exec_resources->last_arg_present == true)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_dprintf(2, "minishell: fork() failure in run_simple_command()\n");
			return ;
		}
		if (pid == 0)
		{
			if (command_node->redirs != NULL)
			{
				if (manage_redirections(command_node->redirs) != 0)
				{
					exit_cleanup(exec_resources, prompt_resources);
					exit(EXIT_FAILURE);
				}
			}
			run_executable(command_node->argv, exec_resources, prompt_resources, NULL);
		}
		signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
		wait(&wstatus);
		init_signals();
		if (WIFEXITED(wstatus))
			exec_resources->curr_exit_status = (WEXITSTATUS(wstatus));
		else
		{
			if (WTERMSIG(wstatus) == SIGINT)
				write(2, "\n", 1);
			else if (WTERMSIG(wstatus) == SIGQUIT)
				ft_dprintf(2, "Quit (core dumped)\n");
			exec_resources->curr_exit_status = (WTERMSIG(wstatus) + 128);
		}
	}
	return ;
}

