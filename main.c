/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/01 01:43:53 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char *av[], char *envp[])
{
	t_prompt_resources	prompt_resources;
	t_exec_resources	exec_resources;
	t_cmd				*curr_command_node;
	
	init_signals();
	if (ac > 1)
	{
		ft_dprintf(2, "No arguments should be given at program startup.\n");
		return (1);
	}
	(void)av;
	exec_resources.local_envp = duplicate_environment(envp); // free
	if (exec_resources.local_envp == NULL)
		return (2);
	check_essential_env_vars(&exec_resources);
	get_var_indexes(&exec_resources); // CALL THIS AGAIN WHEN SETTING OR UNSETTING
	exec_resources.prompt = NULL;
	define_prompt(&exec_resources.prompt, &prompt_resources, exec_resources.local_envp);
	exec_resources.curr_exit_status = 0;
	while (1)
	{
		if (exec_resources.prompt != NULL)
			exec_resources.user_input = readline(exec_resources.prompt); // free
		else
			exec_resources.user_input = readline("42_minishell: ");

		//this is what check the exit if ctrl+D is pressed at any point
		if (!exec_resources.user_input)
    	{
        	ft_printf("exit\n");
        	break;
    	}
		
		add_history(exec_resources.user_input);
		exec_resources.command_list = start_parsing(exec_resources.user_input);
		curr_command_node = exec_resources.command_list;

		while (curr_command_node != NULL)
		{
			// manage_piping_and_redirection(curr_command_node);
			if (curr_command_node->builtin)
				exec_resources.curr_exit_status = (unsigned char)manage_builtin(curr_command_node, &exec_resources, &prompt_resources);	
			else
				exec_resources.curr_exit_status = (unsigned char)run_executable(curr_command_node->argv, &exec_resources);
			if (exec_resources.last_command_present == true)
				update_local_env_last_command(&exec_resources, curr_command_node->argv[0]); // Make sure
			// That the first index is always a command and never a redirection
			curr_command_node = curr_command_node->next;
		}
		free(exec_resources.user_input);
		free_cmds(exec_resources.command_list);
	}
	return (0);
}

// exec_resources to free or clear:
//
// -local_envp and each *local_envp, managed
// -user_input, managed
// -history, managed
