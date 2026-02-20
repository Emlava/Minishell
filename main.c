/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/20 13:15:41 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	size_t	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

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
	while (i < env_var_count) // Should it be i + 1? What's the last variable?
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
	char	**local_envp;
	char	*prompt;
	char	*user_input;
	t_cmd	*command_list;
	// int		prev_exit_status;
	
	if (ac > 1)
	{
		ft_dprintf(2, "No arguments should be given at program startup.\n");
		return (1);
	}
	local_envp = duplicate_environment(envp); // free
	if (local_envp == NULL)
		return (2);
	(void)av;
	define_prompt(&prompt);
	while (1)
	{
		user_input = readline(prompt); // free
		add_history(user_input);
		command_list = start_parsing(user_input);
		//
		printf("This is the first char of the first command: %c\n", command_list->argv[0][0]);
		printf("This is the first command: %s\n", command_list->argv[0]);
		//

		//
		// t_cmd	*curr_command_node;
		// int		i;
		
		// curr_command_node = command_list;
		// while (curr_command_node)
		// {
		// 	i = 0;
		// 	while (curr_command_node->argv[i])
		// 	{
		// 		printf("%s|", curr_command_node->argv[i]);
		// 		i++;
		// 	}
		// 	printf("\nBuiltin: ");
		// 	if (curr_command_node->is_builtin == true)
		// 		printf("yes\n\n");
		// 	else
		// 		printf("no\n\n");
		// 	curr_command_node = curr_command_node->next;
		// }
		//
		
		// while (cmd_list->next != NULL)
		// {
		// 		manage_piping_and_redirection(token_list);
		//		if (command_list->is_builtin == true)
		//		{
		//			// *
		//			// ft_cd here
		//			prev_exit_status = manage_builtin(command_list->argv, prev_exit_status, &prompt);
		//		}
		//		else
		//	 		run_executable(command_list);
		// }
		
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
		free(user_input);
		free_cmds(command_list);
	}
	free_str_arr(local_envp);
	if (ft_strncmp(prompt, "42_minishell: ", 15) != 0)
		free(prompt);
	rl_clear_history();
	return (0);
}

// Resources to free or clear:
//
// -local_envp and each *local_envp, managed
// -user_input, managed
// -history, managed
