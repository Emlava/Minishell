/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:24:22 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/28 02:18:29 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (HEREDOC);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	handle_token(t_cmd **current, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		add_arg(*current, (*tokens)->value);
		if (!(*current)->argv[1])
			(*current)->builtin = get_builtin_type((*current)->argv[0]);
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		(*current)->next = cmd_new();
		*current = (*current)->next;
	}
	else
	{
		add_redir(*current, *tokens);
		*tokens = (*tokens)->next;
	}
}
