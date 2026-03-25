/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:25:10 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/25 10:00:00 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	line_is_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	mark_parse_error(int *exit_status)
{
	if (exit_status)
		*exit_status = 2;
	return (1);
}

static int	parse_has_error(t_token *tokens, int *exit_status)
{
	if (!tokens)
		return (mark_parse_error(exit_status));
	if (!check_syntax(tokens))
	{
		mark_parse_error(exit_status);
		free_tokens(tokens);
		return (1);
	}
	return (0);
}

t_cmd	*start_parsing(char *line, char **envp, struct s_new_exports *ne,
				int *exit_status)
{
	t_token	*tokens;
	t_cmd	*t_cmds;
	int		status;

	if (!line || line_is_blank(line))
		return (NULL);
	status = 0;
	if (exit_status)
		status = *exit_status;
	tokens = lexer(line, envp, ne, status);
	if (parse_has_error(tokens, exit_status))
		return (NULL);
	t_cmds = parse_tokens(tokens);
	free_tokens(tokens);
	return (t_cmds);
}
