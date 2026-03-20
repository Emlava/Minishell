/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:07:55 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 12:39:00 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	input_redirection(t_redir *redirection_info)
{
	int		target_fd;
	char	*err_str;

	target_fd = open(redirection_info->target, O_RDONLY);
	if (target_fd == -1)
	{
		err_str = ft_strjoin("minishell: ", redirection_info->target);
		if (!err_str)
		{
			ft_dprintf(2, "minishell: malloc() failure in input_redirection()\n");
			return (1);
		}
		perror(err_str);
		free(err_str);
		return (2);
	}
	if (dup2(target_fd, STDIN_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2() failure in input_redirection()\n");
		return (3);
	}
	close(target_fd);
	return (0);
}

int	output_redirection(t_redir *redirection_info)
{
	int		target_fd;
	char	*err_str;

	target_fd = open(redirection_info->target, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (target_fd == -1)
	{
		err_str = ft_strjoin("minishell: ", redirection_info->target);
		if (!err_str)
		{
			ft_dprintf(2, "minishell: malloc() failure in output_redirection()\n");
			return (1);
		}
		perror(err_str);
		free(err_str);
		return (2);
	}
	if (dup2(target_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2() failure in output_redirection()\n");
		return (3);
	}
	close(target_fd);
	return (0);
}

int	output_redirection_append(t_redir *redirection_info)
{
	int		target_fd;
	char	*err_str;

	target_fd = open(redirection_info->target, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (target_fd == -1)
	{
		err_str = ft_strjoin("minishell: ", redirection_info->target);
		if (!err_str)
		{
			ft_dprintf(2, "minishell: malloc() failure in output_redirection_append()\n");
			return (1);
		}
		perror(err_str);
		free(err_str);
		return (2);
	}
	if (dup2(target_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "minishell: dup2() failure in output_redirection_append()\n");
		return (3);
	}
	close(target_fd);
	return (0);
}

int	manage_redirections(t_redir *redirection_info)
{
	while (redirection_info)
	{
		if (redirection_info->type == REDIR_IN)
		{
			if (input_redirection(redirection_info) != 0)
			return (1);
		}
		else if (redirection_info->type == REDIR_OUT)
		{
			if (output_redirection(redirection_info) != 0)
			return (2);
		}
		else if (redirection_info->type == REDIR_APPEND)
		{
			if (output_redirection_append(redirection_info) != 0)
			return (3);
		}
		// else
		// {}
		redirection_info = redirection_info->next;
	}
	return (0);
}

