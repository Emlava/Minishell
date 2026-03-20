/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 19:47:35 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	manage_builtin(t_cmd *command, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	if (command->builtin == BUILTIN_ECHO)
		return (ft_echo(command->argv));
	if (command->builtin == BUILTIN_CD)
		return (ft_cd(command->argv, exec_resources, prompt_resources));
	if (command->builtin == BUILTIN_PWD)
		return (ft_pwd(command->argv, exec_resources->local_envp));
	if (command->builtin == BUILTIN_EXPORT)
		return (ft_export(command->argv, exec_resources->local_envp,
				&exec_resources->new_exports));
	if (command->builtin == BUILTIN_UNSET)
		return (ft_unset(command->argv, exec_resources));
	if (command->builtin == BUILTIN_ENV)
		return (ft_env(command->argv, exec_resources));
	else
		return (ft_exit(command->argv, exec_resources, prompt_resources));
}
