/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/13 16:41:01 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
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
	// if piping or redirections: close fds
	return ;
}

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
			run_executable(command_node->argv, exec_resources, prompt_resources);
		signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
		wait(&wstatus);
		init_signals();
		if (WIFEXITED(wstatus))
			exec_resources->curr_exit_status = (WEXITSTATUS(wstatus));
		else
		{
			if (WTERMSIG(wstatus) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(wstatus) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			exec_resources->curr_exit_status = (WTERMSIG(wstatus) + 128);
		}
	}
	return ;
}

static void	run_command_in_subshell(t_cmd *command_node, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
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
		run_executable(command_node->argv, exec_resources, prompt_resources);
	exit_cleanup(exec_resources, prompt_resources);
	exit(exit_status);
}

// Returns the exit status of the last child process.
static int	wait_for_all_children(t_pids *pid_list)
{
	int	wstatus;

	while (pid_list != NULL)
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
				write(1, "\n", 1);
			else if (WTERMSIG(wstatus) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
		}
		return (WTERMSIG(wstatus) + 128);
	}
}

void	run_compound_command(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	t_cmd	*command_node;
	t_pids	*pid_list;
	t_pids	*pid_node;


	command_node = exec_resources->command_list;
	pid_list = malloc(sizeof(t_pids));
	if (!pid_list)
	{
		ft_dprintf(2, "minishell: malloc() failure in run_compound_command()\n");
		return ;
	}
	pid_list->next = NULL;
	pid_node = pid_list;
	while (command_node != NULL)
	{
		// Pipe
		// Manage possible redirections
		// Fork (Create linked list of pids)
		pid_node->pid = fork();
		if (pid_node->pid == -1)
		{
			ft_dprintf(2, "minishell: fork() failure in run_compound_command()\n");
			wait_for_all_children(pid_list);
			free_pid_list(pid_list);
			return ;
		}
		if (pid_node->pid == 0)
		{
			free_pid_list(pid_list);
			run_command_in_subshell(command_node, exec_resources, prompt_resources);
		}
		command_node = command_node->next;
		if (command_node != NULL)
		{
			pid_node->next = malloc(sizeof(t_pids));
			if (!pid_node)
			{
				ft_dprintf(2, "minishell: malloc() failure in run_compound_command()\n");
				wait_for_all_children(pid_list);
				free_pid_list(pid_list);
				return ;
			}
			pid_node = pid_node->next;
			pid_node->next = NULL;
		}
	}
	// Here we waitpid() in a loop, going through the list of pids.
	// We update curr_exit_status only when reaching the last node.
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_resources->curr_exit_status = wait_for_all_children(pid_list);
	init_signals();
	free_pid_list(pid_list);
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
	exec_resources.command_list = NULL;
	define_prompt(&exec_resources.prompt, &prompt_resources, exec_resources.local_envp, exec_resources.internal_pwd);
	exec_resources.curr_exit_status = 0;
	while (1)
	{
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
			start_parsing(exec_resources.user_input, exec_resources.local_envp,\
			exec_resources.new_exports, exec_resources.curr_exit_status);
		free(exec_resources.user_input);
		if (exec_resources.command_list == NULL)
			continue ;
		if (exec_resources.command_list->next == NULL)
			run_simple_command(&exec_resources, &prompt_resources);
		else
			run_compound_command(&exec_resources, &prompt_resources);
		free_cmds(exec_resources.command_list);
	}
	return (0);
}
