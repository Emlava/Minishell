/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/13 12:38:29 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*prompt;
	char	*user_input;
	
	//
	char	*test_av[3];
	//
	if (ac > 1)
	{
		printf("No arguments should be given at program startup.\n");
		return (1);
	}
	(void)av;
	define_prompt(&prompt); // If the command is cd, we'll have to free prompt and 
	// call this again

	while (1)
	{
		user_input = readline(prompt); // free
		
		//
		test_av[0] = user_input;
		test_av[1] = NULL;
		test_av[2] = NULL;
		//
		
		add_history(user_input);
		// cmd_list = parsing_function(user_input);
		// manage_piping_and_redirection(token_list);
		// run_command(token_list);
		
		if (ft_strncmp(user_input, "exit", 5) == 0)
		{
			free(user_input);
			printf("exit\n");
			break ;
		}
		//
		pid_t	pid = fork();
		if (pid == 0)
		{
			char	*absolute_path = ft_strjoin("/usr/bin/", user_input);
			if (execve(absolute_path, test_av, envp) == -1) // Run simple commands without arguments nor options
			{
				printf("minishell: "); // Use ft_strjoin() instead
				perror(user_input);
				if (ft_strncmp(prompt, "42_minishell: ", 15) != 0)
					free(prompt);
				free(user_input);
				free(absolute_path);
				rl_clear_history();
				return (1);
			}
		}
		else
			waitpid(pid, NULL, 0);
		//

		free(user_input);
	}
	if (ft_strncmp(prompt, "42_minishell: ", 15) != 0)
		free(prompt);
	rl_clear_history();
	return (0);
}

// Resources to free or clear:
//
// Allocated or used inside main.c:
// -user_input, freed
// -history, cleared
//
// Allocated inside manage_prompt.c:
// -user (in some cases) in define_prompt(), freed
// -host_or_computer (in some cases) in define_prompt(), freed
// -working_dir (in some cases) in define_prompt() and
// format_working_dir, both freed
// -tmp (in some cases {two possible instances}) in define_prompt(), freed
// -prompt (if it's not "42_minishell: "), freed
