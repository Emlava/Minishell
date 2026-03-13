/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 02:19:06 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/04 16:05:46 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../execution/execution.h"

char	*get_var_value(char *var, t_parse_ctx *ctx)
{
	char			*value;
	t_new_exports	*exp_node;

	value = get_local_env(ctx->envp, var);
	if (!value)
	{
		exp_node = get_local_exp(&(ctx->new_exports), var);
		if (exp_node)
			value = exp_node->var + ft_strlen(var) + 1;
	}
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*process_double_content(char *word, char *tmp, t_parse_ctx *ctx)
{
	int	start;
	int	plain_start;

	start = 0;
	while (tmp[start])
	{
		if (tmp[start] == '$')
			word = append_variable(word, tmp, &start, ctx);
		else
		{
			plain_start = start;
			while (tmp[start] && tmp[start] != '$')
				start++;
			word = ft_strjoin_free(word,
					ft_substr(tmp, plain_start, start - plain_start));
		}
	}
	return (word);
}

char	*handle_quote_case(char *word, char *line, int *i, t_parse_ctx *ctx)
{
	if (line[*i] == '\'')
	{
		*(ctx->quoted) = 1;
		return (append_single_quoted(word, line, i));
	}
	if (line[*i] == '"')
	{
		*(ctx->quoted) = 1;
		return (append_double_quoted(word, line, i, ctx));
	}
	return (word);
}

char	*handle_word_char(char *word, char *line, int *i, t_parse_ctx *ctx)
{
	if (line[*i] == '$')
		return (append_variable(word, line, i, ctx));
	return (append_plain(word, line, i));
}
