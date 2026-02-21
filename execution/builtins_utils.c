/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:18:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/21 22:43:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	update_local_environment(char **local_envp)
// {
	
// }

void	exit_cleanup(t_resources *resources)
{
	free(resources->user_input);
	free_cmds(resources->command_list);
	free_str_arr(resources->local_envp);
	if (resources->prompt != NULL)
		free(resources->prompt);
	rl_clear_history();
	// if piping or redirections: close fds
	return ;
}
