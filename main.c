/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/21 23:21:40 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_environment(char *envp[])
{
	int		env_var_count;
	int		i;
	char	**env_duplicate;

	env_var_count = 0;
	while (envp[env_var_count] != NULL)
		env_var_count++;
	env_duplicate = malloc(sizeof(char*) * (env_var_count + 1)); // free
	if (env_duplicate == NULL)
		return (NULL);
	i = 0;
	while (i < env_var_count)
	{
		env_duplicate[i] = ft_strdup(envp[i]); // free each
		if (env_duplicate[i] == NULL)
		{
			free_str_arr(env_duplicate);
			return (NULL);
		}
		i++;
	}
	env_duplicate[i] = NULL;
	return (env_duplicate);
}

int	main(int ac, char *av[], char *envp[])
{
	t_resources	resources;
	t_cmd		*curr_command_node;
	
	if (ac > 1)
	{
		ft_dprintf(2, "No arguments should be given at program startup.\n");
		return (1);
	}
	resources.local_envp = duplicate_environment(envp); // free
	if (resources.local_envp == NULL)
		return (2);
	(void)av;
	resources.prompt = NULL;
	define_prompt(&resources.prompt, resources.local_envp);
	resources.curr_exit_status = 0;
	while (1)
	{
		if (resources.prompt != NULL)
			resources.user_input = readline(resources.prompt); // free
		else
			resources.user_input = readline("42_minishell: ");
		add_history(resources.user_input);
		resources.command_list = start_parsing(resources.user_input);
		curr_command_node = resources.command_list;

		while (curr_command_node != NULL)
		{
			//
			// define_prompt(&resources.prompt, resources.local_envp);
			//
			// manage_piping_and_redirection(curr_command_node);
			if (curr_command_node->builtin)
				resources.curr_exit_status = manage_builtin(curr_command_node, &resources);
			// else
			// 	resources.curr_exit_status = run_executable(curr_command_node->argv, &resources);
			curr_command_node = curr_command_node->next;
		}
		
		// // This will be in run_executable()
		// pid_t	pid = fork();
		// if (pid == 0)
		// {
		// 	char	*absolute_path = ft_strjoin("/usr/bin/", user_input);
		// 	if (execve(absolute_path, command_list->argv, envp) == -1) // Run simple commands without arguments nor options
		// 	{
		// 		printf("minishell: "); // Use ft_strjoin() instead
		// 		perror(user_input);
		// 		if (ft_strncmp(prompt, "42_minishell: ", 15) != 0)
		// 			free(prompt);
		// 		free(user_input);
		// 		free(absolute_path);
		// 		rl_clear_history();
		// 		return (1);
		// 	}
		// }
		// else
		// 	waitpid(pid, NULL, 0); // Change this so that it gets the return status
		//
		free(resources.user_input);
		free_cmds(resources.command_list);
	}
	free_str_arr(resources.local_envp);
	if (resources.prompt != NULL)
		free(resources.prompt);
	// close fds
	rl_clear_history();
	return (0);
}

// Resources to free or clear:
//
// -local_envp and each *local_envp, managed
// -user_input, managed
// -history, managed
