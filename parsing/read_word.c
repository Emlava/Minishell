/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:40:42 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/28 02:38:39 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*append_plain(char *word, char *line, int *i)
{
	char	*tmp;
	int		start;

	start = *i;
	while (line[*i]
		&& !ft_isspace(line[*i])
		&& line[*i] != '|'
		&& line[*i] != '<'
		&& line[*i] != '>'
		&& line[*i] != '\''
		&& line[*i] != '"')
		(*i)++;
	tmp = ft_substr(line, start, *i - start);
	return (ft_strjoin_free(word, tmp));
}

char	*append_variable(char *word, char *line, int *i)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	if (line[*i] == '?')
	{
		value = ft_itoa(g_exit_status);
		(*i)++;
		return (ft_strjoin_free(word, value));
	}
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return (ft_strjoin_free(word, ft_strdup("$")));
	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var = ft_substr(line, start, *i - start);
	value = getenv(var);
	free(var);
	if (!value)
		value = ft_strdup("");
	else
		value = ft_strdup(value);
	return (ft_strjoin_free(word, value));
}

char	*append_single_quoted(char *word, char *line, int *i)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		ft_printf("Quote arent closed\n");
		free(word);
		return (NULL);
	}
	tmp = ft_substr(line, start, *i - start);
	word = ft_strjoin_free(word, tmp);
	(*i)++;
	return (word);
}

char	*append_double_quoted(char *word, char *line, int *i)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (!line[*i])
	{
		ft_printf("Quote arent closed\n");
		free(word);
		return (NULL);
	}
	tmp = ft_substr(line, start, *i - start);
	word = process_double_content(word, tmp);
	free(tmp);
	(*i)++;
	return (word);
}

char	*read_word(char *line, int *i, int *quoted)
{
	char	*word;

	word = ft_strdup("");
	while (line[*i]
		&& !ft_isspace(line[*i])
		&& line[*i] != '|'
		&& line[*i] != '<'
		&& line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '"')
			word = handle_quote_case(word, line, i, quoted);
		else
			word = handle_word_char(word, line, i);
	}
	return (word);
}
