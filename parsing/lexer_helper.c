/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:32:12 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/20 13:21:31 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	handle_operator(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '|')
	{
		token_add_back(tokens, token_new(TOKEN_PIPE, NULL));
		(*i)++;
	}
	else if (line[*i] == '<')
		handle_input_redir(line, i, tokens);
	else if (line[*i] == '>')
		handle_output_redir(line, i, tokens);
}

void	handle_input_redir(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '<')
	{
		token_add_back(tokens, token_new(TOKEN_HEREDOC, NULL));
		*i += 2;
	}
	else
	{
		token_add_back(tokens, token_new(TOKEN_REDIR_IN, NULL));
		(*i)++;
	}
}

void	handle_output_redir(char *line, int *i, t_token **tokens)
{
	if (line[*i + 1] == '>')
	{
		token_add_back(tokens, token_new(TOKEN_REDIR_APPEND, NULL));
		*i += 2;
	}
	else
	{
		token_add_back(tokens, token_new(TOKEN_REDIR_OUT, NULL));
		(*i)++;
	}
}

int	handle_word(char *line, int *i, t_token **tokens)
{
	char	*word;
	int		quoted;
	t_token	*new;

	quoted = 0;
	word = read_word(line, i, &quoted);
	if (!word)
		return (0);
	new = token_new(TOKEN_WORD, word);
	new->quoted = quoted;
	token_add_back(tokens, new);
	return (1);
}
