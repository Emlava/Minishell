/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:38:25 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/16 17:04:37 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_pipe_error(t_token *tmp)
{
	if (!tmp->next || tmp->next->type == TOKEN_PIPE)
	{
		ft_printf("syntax error near '|'\n");
		return (0);
	}
	return (1);
}

static int	check_redir_error(t_token *tmp)
{
	if (!tmp->next || tmp->next->type != TOKEN_WORD)
	{
		ft_printf("syntax error near redirection\n");
		return (0);
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_printf("syntax error near '|'\n");
		return (0);
	}
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE
			&& !check_pipe_error(tmp))
			return (0);
		if ((tmp->type == TOKEN_REDIR_IN
				|| tmp->type == TOKEN_REDIR_OUT
				|| tmp->type == TOKEN_REDIR_APPEND
				|| tmp->type == TOKEN_HEREDOC)
			&& !check_redir_error(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
