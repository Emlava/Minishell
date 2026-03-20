/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:11:13 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 14:02:07 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//
static int	initialize_pipe_node(t_pipes **pipe_node)
{
	*pipe_node = malloc(sizeof(t_pipes));
	if (!*pipe_node)
		return (1);
	(*pipe_node)->next = NULL;
	if (pipe((*pipe_node)->pipe) == -1)
		return (2);
	return (0);
}

static int	initialize_pid_node(t_pids **pid_node, int child_count)
{
	*pid_node = malloc(sizeof(t_pids));
	if (!*pid_node)
		return (1);
	(*pid_node)->pid = -1;
	(*pid_node)->child_nbr = child_count;
	(*pid_node)->next = NULL;
	return (0);
}

static int	create_pipe_and_pib_lists(t_pipes **pipe_list, t_pids **pid_list, int nbr_of_children)
{
	int		child_count;
	t_pipes	*pipe_node;
	t_pids	*pid_node;

	child_count = 1;
	if (initialize_pipe_node(pipe_list) != 0)
		return (1);
	if (initialize_pid_node(pid_list, child_count) != 0)
		return (2);
	pipe_node = *pipe_list;
	pid_node = *pid_list;
	while (++child_count <= nbr_of_children)
	{
		if (child_count < nbr_of_children)
		{
			if (initialize_pipe_node(&pipe_node->next) != 0)
			{
				free_pipe_list(*pipe_list);
				free_pid_list(*pid_list);
				return (1);
			}
			pipe_node = pipe_node->next;
		}
		if (initialize_pid_node(&pid_node->next, child_count) != 0)
		{
			free_pipe_list(*pipe_list);
			free_pid_list(*pid_list);
			return (2);
		}
		pid_node = pid_node->next;
	}
	return (0);
}
//


static int	count_commands(t_cmd *command_list)
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

static void	run_command_in_subshell(t_cmd *command_node, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources, t_pipes *pipe_list)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
	exit_status = 0;
	if (command_node->builtin)
		exit_status = manage_builtin(command_node, exec_resources, prompt_resources);	
	if (exec_resources->last_arg_present == true && command_node->next == NULL)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
		run_executable(command_node->argv, exec_resources, prompt_resources, pipe_list);
	exit_cleanup(exec_resources, prompt_resources);
	free_pipe_list(pipe_list);
	exit(exit_status);
}

// Returns the exit status of the last child process.
static int	wait_for_all_children(t_pids *pid_list)
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
				ft_dprintf(2, "Quit (core dumped)\n");
		}
		return (WTERMSIG(wstatus) + 128);
	}
}

static void	exit_failure(t_pipes *pipes, t_pids *pids,
	t_exec_resources *res, t_prompt_resources *prompt)
{
	free_pipe_list(pipes);
	free_pid_list(pids);
	exit_cleanup(res, prompt);
	ft_dprintf(2, "minishell: dup2() failure\n");
	exit(EXIT_FAILURE);
}

void	run_compound_command(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	t_pipes	*pipe_list;
	t_pipes	*pipe_node;
	t_pids	*pid_list;
	t_pids	*pid_node;
	t_cmd	*command_node;

	if (create_pipe_and_pib_lists(&pipe_list, &pid_list, count_commands(exec_resources->command_list)) != 0)
	{
		exit_cleanup(exec_resources, prompt_resources);
		ft_dprintf(2, "minishell: fatal error occurred while managing a pipe chain\n");
		exit(EXIT_FAILURE);
	}
	pipe_node = pipe_list;
	pid_node = pid_list;
	command_node = exec_resources->command_list;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (command_node != NULL)
	{
		pid_node->pid = fork();
		if (pid_node->pid == -1)
		{
			ft_dprintf(2, "minishell: fork() failure in run_compound_command()\n");
			wait_for_all_children(pid_list);
			free_pipe_list(pipe_list);
			free_pid_list(pid_list);
			return ;
		}

		// Child
		if (pid_node->pid == 0)
		{
			//PIPES
			if (pid_node->child_nbr == 1)
			{
				if (command_node->next != NULL)
				{
					if (dup2(pipe_node->pipe[1], STDOUT_FILENO) == -1)
						exit_failure(pipe_list, pid_list, exec_resources, prompt_resources);
				}
				close_unused_fds(pipe_node);
			}
			else
			{
				if (dup2(pipe_node->pipe[0], STDIN_FILENO) == -1)
					exit_failure(pipe_list, pid_list, exec_resources, prompt_resources);
				if (pid_node->next != NULL)
				{
					if (dup2(pipe_node->next->pipe[1], STDOUT_FILENO) == -1)
						exit_failure(pipe_list, pid_list, exec_resources, prompt_resources);
					close_unused_fds(pipe_node->next);
				}
				close(pipe_node->pipe[0]);
			}
			//HEREDOC
			t_redir	*r;
			int		heredoc_fd;
			r = command_node->redirs;
			heredoc_fd = -1;
			while (r)
			{
				if (r->type == HEREDOC)
					heredoc_fd = r->fd;
				r = r->next;
			}
			if (heredoc_fd != -1)
			{
				if (dup2(heredoc_fd, STDIN_FILENO) == -1)
					exit_failure(pipe_list, pid_list, exec_resources, prompt_resources);
				close(heredoc_fd);
			}
			free_pid_list(pid_list);
			run_command_in_subshell(command_node,
				exec_resources, prompt_resources, pipe_list);
		}

		// Parent
		if (pid_node->child_nbr == 1)
			close(pipe_node->pipe[1]);
		else
		{
			close(pipe_node->pipe[0]);
			if (pid_node->next != NULL)
			{
				pipe_node = pipe_node->next;
				close(pipe_node->pipe[1]);
			}
		}
		pid_node = pid_node->next;
		command_node = command_node->next;
	}
	exec_resources->curr_exit_status = wait_for_all_children(pid_list);
	init_signals();
	free_pipe_list(pipe_list);
	free_pid_list(pid_list);
	return ;
}
