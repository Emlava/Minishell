/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:10:45 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/21 14:20:46 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	run_exec_in_child(t_cmd *command_node,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(2, "minishell: \
			fork() failure in run_simple_command()\n");
		return (1);
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
		run_executable(command_node->argv, exec_resources,
			prompt_resources, NULL);
	}
	return (0);
}

static int	get_child_exit_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
	{
		if (WTERMSIG(wstatus) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_dprintf(2, "Quit (core dumped)\n");
		return (WTERMSIG(wstatus) + 128);
	}
}

void	run_simple_command(t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	t_cmd	*command_node;
	int		wstatus;

	command_node = exec_resources->command_list;
	if (command_node->builtin)
		exec_resources->curr_exit_status = manage_builtin(command_node,
				exec_resources, prompt_resources);
	if (exec_resources->last_arg_present == true)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
	{
		if (run_exec_in_child(command_node, exec_resources,
				prompt_resources) != 0)
			return ;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&wstatus);
		init_signals();
		exec_resources->curr_exit_status = get_child_exit_status(wstatus);
	}
	return ;
}
