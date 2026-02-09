/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/09 20:11:23 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*prompt;
	char	*user_input;
	
	//
	(void)ac;
	(void)av;
	(void)envp;
	//
	define_prompt(&prompt); // If a command is cd, we'll have to free prompt and 
	// call this again
	while (1)
	{
		user_input = readline(prompt); // free
		add_history(user_input);
		// parsing_function(user_input, cmd_list);
		if (ft_strncmp(user_input, "exit", 5) == 0)
		{
			free(user_input);
			break ;
		}

		free(user_input);
	}
	if (ft_strncmp(prompt, "42_minishell: ", 15) != 0)
		free(prompt);
	rl_clear_history();
	return (0);
}

// Resources to free or clear:
//
// Allocated inside manage_prompt.c:
// -user (in some cases) in define_prompt(), freed
// -host_or_computer (in some cases) in define_prompt(), freed
// -working_dir (in some cases) in define_prompt() and
// format_working_dir, both freed
// -tmp (in some cases) in define_prompt(), freed
// -prompt (if it's not "42_minishell: "), freed
//
// Allocated or used inside main.c:
// -user_input, freed
// -history, cleared
