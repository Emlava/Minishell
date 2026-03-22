/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 10:50:25 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	create_std_fd_backup(t_redir *redir_info)
{
	if (redir_info->type == REDIR_IN || redir_info->type == HEREDOC)
		return (dup(STDIN_FILENO));
	else
		return (dup(STDOUT_FILENO));
}

static void	restore_stdin_or_stdout(t_redir *redir_info, int stdfd_backup)
{
	if (redir_info->type == REDIR_IN || redir_info->type == HEREDOC)
		dup2(stdfd_backup, STDIN_FILENO);
	else
		dup2(stdfd_backup, STDOUT_FILENO);
	close(stdfd_backup);
	return ;
}

static int	run_builtin(t_cmd *command, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	if (command->builtin == BUILTIN_ECHO)
		return (ft_echo(command->argv));
	else if (command->builtin == BUILTIN_CD)
		return (ft_cd(command->argv, exec_resources, prompt_resources));
	else if (command->builtin == BUILTIN_PWD)
		return (ft_pwd(command->argv, exec_resources->local_envp));
	else if (command->builtin == BUILTIN_EXPORT)
		return (ft_export(command->argv, exec_resources->local_envp,
				&exec_resources->new_exports));
	else if (command->builtin == BUILTIN_UNSET)
		return (ft_unset(command->argv, exec_resources));
	else if (command->builtin == BUILTIN_ENV)
		return (ft_env(command->argv, exec_resources));
	else
		return (ft_exit(command->argv, exec_resources, prompt_resources));
}

int	manage_builtin(t_cmd *command, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	int	stdfd_backup;
	int	return_value;

	if (command->redirs != NULL)
	{
		stdfd_backup = create_std_fd_backup(command->redirs);
		if (stdfd_backup == -1)
		{
			ft_dprintf(2, "minishell: dup() error\n");
			return (1);
		}
		if (manage_redirections(command->redirs) != 0)
			return (2);
	}
	return_value = run_builtin(command, exec_resources, prompt_resources);
	if (command->redirs != NULL)
		restore_stdin_or_stdout(command->redirs, stdfd_backup);
	return (return_value);
}
