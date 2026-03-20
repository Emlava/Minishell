/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 13:43:54 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (process_all_heredocs(exec_resources.command_list, &exec_resources))
		{
			close(0);
			open("/dev/tty", O_RDONLY);
			continue ;
		}
		if (exec_resources.command_list->next == NULL
			&& exec_resources.command_list->builtin != BUILTIN_NONE)
		{
			exec_resources.curr_exit_status =
				manage_builtin(exec_resources.command_list,
					&exec_resources, &prompt_resources);
		}
		else
		{
			run_compound_command(&exec_resources, &prompt_resources);
		}
		
		//
		// Printing every member of each command_list node
		// t_cmd *command_list_node;
		// command_list_node = exec_resources.command_list;
		// while (command_list_node)
		// {
		// 	t_redir *redir_node = command_list_node->redirs;
		// 	int i = 0;
		// 	if (command_list_node->argv[0] == NULL)
		// 	{
		// 		printf("argv[0] is NULL\n");
		// 		continue ;
		// 	}
		// 	while (command_list_node->argv[i])
		// 	{
		// 		printf("%s\n", command_list_node->argv[i]);
		// 		i++;
		// 	}
		// 	printf("\n");
		// 	if (!redir_node)
		// 		printf("No redirections present\n\n");
		// 	else
		// 	{
		// 		while (redir_node)
		// 		{
		// 			if (redir_node->target == NULL)
		// 				printf("target is NULL\n");
		// 			printf("type: %d\ntarget: %s\nquoted: %d\n\n", redir_node->type, redir_node->target, redir_node->quoted);
		// 			redir_node = redir_node->next;
		// 		}
		// 	}
		// 	command_list_node = command_list_node->next;
		// }
		// //
		
		free_cmds(exec_resources.command_list);
	}
	return (0);
}
