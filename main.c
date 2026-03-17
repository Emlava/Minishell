/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/17 20:08:04 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_simple_command(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	t_cmd	*command_node;
	pid_t	pid;
	int		wstatus;

	command_node = exec_resources->command_list;
	// Manage possible redirections
	if (command_node->builtin)
		exec_resources->curr_exit_status = manage_builtin(command_node, exec_resources, prompt_resources);	
	if (exec_resources->last_arg_present == true)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_dprintf(2, "minishell: fork() failure in run_compound_command()\n");
			return ;
		}
		if (pid == 0)
			run_executable(command_node->argv, exec_resources, prompt_resources, NULL);
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
    signal(SIGQUIT, SIG_DFL);
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
			if (pid_node->child_nbr == 1)
			{
				if (dup2(pipe_node->pipe[1], STDOUT_FILENO) == -1)
				{
					free_pipe_list(pipe_list);
					free_pid_list(pid_list);
					ft_dprintf(2, "minishell: dup2() failure in run_compound_command()\n");
					exit(EXIT_FAILURE);
				}
				close_unused_fds(pipe_node);
			}
			else
			{
				if (dup2(pipe_node->pipe[0], STDIN_FILENO) == -1)
				{
					free_pipe_list(pipe_list);
					free_pid_list(pid_list);
					ft_dprintf(2, "minishell: dup2() failure in run_compound_command()\n");
					exit(EXIT_FAILURE);
				}
				if (pid_node->next != NULL)
				{
					if (dup2(pipe_node->next->pipe[1], STDOUT_FILENO) == -1)
					{
						free_pipe_list(pipe_list);
						free_pid_list(pid_list);
						ft_dprintf(2, "minishell: dup2() failure in run_compound_command()\n");
						exit(EXIT_FAILURE);
					}
					close_unused_fds(pipe_node->next);
				}
				close(pipe_node->pipe[0]);
			}
			free_pid_list(pid_list);
			// Manage possible redirections
			run_command_in_subshell(command_node, exec_resources, prompt_resources, pipe_list);
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_resources->curr_exit_status = wait_for_all_children(pid_list);
	init_signals();
	free_pipe_list(pipe_list);
	free_pid_list(pid_list);
	return ;
}

int	main(int ac, char *av[], char *envp[])
{
	t_prompt_resources	prompt_resources;
	t_exec_resources	exec_resources;
	
	init_signals();
	if (ac > 1)
	{
		ft_dprintf(2, "No arguments should be given at program startup.\n");
		return (1);
	}
	(void)av;
	exec_resources.internal_pwd = getenv("PWD");
	if (!exec_resources.internal_pwd)
	{
		ft_dprintf(2, "It seems like you naughtily removed an essential value from the parent environment.\n");
		ft_dprintf(2, "This shell won't run under those conditions.\n");
		return (2);
	}
	exec_resources.internal_pwd = ft_strdup(exec_resources.internal_pwd); // free
	exec_resources.local_envp = duplicate_environment(envp); // free
	if (exec_resources.local_envp == NULL)
		return (3);
	check_essential_env_vars(&exec_resources);
	get_var_indexes(&exec_resources);
	exec_resources.new_exports = NULL;
	exec_resources.prompt = NULL;
	define_prompt(&exec_resources.prompt, &prompt_resources, exec_resources.local_envp, exec_resources.internal_pwd);
	exec_resources.curr_exit_status = 0;
	while (1)
	{
		exec_resources.command_list = NULL;
		if (exec_resources.prompt != NULL)
			exec_resources.user_input = readline(exec_resources.prompt); // free
		else
			exec_resources.user_input = readline("42_minishell: ");

		if (g_signal != 0)
		{
			exec_resources.curr_exit_status = g_signal;
			g_signal = 0;
		}
		//this is what check the exit if ctrl+D is pressed at any point
		if (!exec_resources.user_input)
    	{
        	ft_printf("exit\n");
			exit_cleanup(&exec_resources, &prompt_resources);
        	return (exec_resources.curr_exit_status); // Check
    	}
		
		add_history(exec_resources.user_input);
		exec_resources.command_list =
			start_parsing(exec_resources.user_input, exec_resources.local_envp,
			exec_resources.new_exports, exec_resources.curr_exit_status);
		free(exec_resources.user_input);
		if (exec_resources.command_list == NULL)
			continue ;
		// if (exec_resources.command_list->next == NULL)
		// 	run_simple_command(&exec_resources, &prompt_resources);
		// else
		// 	run_compound_command(&exec_resources, &prompt_resources);
		
		//
		// Printing every member of each command_list node
		t_cmd *command_list_node;
		command_list_node = exec_resources.command_list;
		while (command_list_node)
		{
			t_redir *redir_node = command_list_node->redirs;
			int i = 0;
			while (command_list_node->argv[i])
			{
				printf("%s\n", command_list_node->argv[i]);
				i++;
			}
			printf("\n");
			if (!redir_node)
				printf("No redirections present\n\n");
			else
			{
				while (redir_node)
				{
					if (redir_node->target == NULL)
						printf("target is NULL\n");
					printf("type: %d\ntarget: %s\nquoted: %d\n\n", redir_node->type, redir_node->target, redir_node->quoted);
					redir_node = redir_node->next;
				}
			}
			command_list_node = command_list_node->next;
		}
		//
		
		free_cmds(exec_resources.command_list);
	}
	return (0);
}
