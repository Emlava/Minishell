/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:18:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/26 13:51:22 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_non_reiterative_path(char **argv)
{

}

void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	free(exec_resources->user_input);
	free_cmds(exec_resources->command_list);
	free_str_arr(exec_resources->local_envp);
	if (exec_resources->prompt != NULL)
	{
		free(exec_resources->prompt);
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
	}
	rl_clear_history();
	// if piping or redirections: close fds
	return ;
}
