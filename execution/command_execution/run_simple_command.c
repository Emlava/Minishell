/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:10:45 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/26 19:51:58 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redir_loop(t_cmd *command_node, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	t_redir	*redir_node;

	redir_node = command_node->redirs;
	while (redir_node != NULL)
	{
		if (manage_redirections(redir_node) != 0)
		{
			exit_cleanup(exec_resources, prompt_resources);
			exit(EXIT_FAILURE);
		}
		redir_node = redir_node->next;
	}
	return ;
}

static int	run_exec_in_child(t_cmd *command_node,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources,
	pid_t *child_pid)
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir_loop(command_node, exec_resources, prompt_resources);
		run_executable(command_node->argv, exec_resources,
			prompt_resources, NULL);
	}
	*child_pid = pid;
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
		{
			if (WCOREDUMP(wstatus))
				ft_dprintf(2, "Quit (core dumped)\n");
			else
				ft_dprintf(2, "Quit\n");
		}
		return (WTERMSIG(wstatus) + 128);
	}
}

void	run_simple_command(t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	t_cmd	*command_node;
	int		wstatus;
	pid_t	child_pid;

	command_node = exec_resources->command_list;
	if (command_node->builtin)
		exec_resources->curr_exit_status = manage_builtin(command_node,
				exec_resources, prompt_resources);
	if (exec_resources->last_arg_present == true)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
	{
		if (run_exec_in_child(command_node, exec_resources,
				prompt_resources, &child_pid) != 0)
			return ;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(child_pid, &wstatus, 0);
		init_signals();
		exec_resources->curr_exit_status = get_child_exit_status(wstatus);
	}
	return ;
}
