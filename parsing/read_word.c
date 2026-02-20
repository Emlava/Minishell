/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:40:42 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/16 17:54:13 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*append_plain(char *word, char *line, int *i)
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

static char	*append_variable(char *word, char *line, int *i)
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

static char	*append_single_quoted(char *word, char *line, int *i)
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

static char	*append_double_quoted(char *word, char *line, int *i)
{
	char	*tmp;
	int		start;
	int		plain_start;

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
	start = 0;
	while (tmp[start])
	{
		if (tmp[start] == '$')
			word = append_variable(word, tmp, &start);
		else
		{
			plain_start = start;
			while (tmp[start] && tmp[start] != '$')
				start++;
			word = ft_strjoin_free(word, ft_substr(tmp, plain_start, start - plain_start));
		}
	}
	free(tmp);
	(*i)++;
	return (word);
}

char	*read_word(char *line, int *i, int *quoted)
{
	char	*word;

	word = ft_strdup("");
	while (
		line[*i]
		&& !ft_isspace(line[*i])
		&& line[*i] != '|'
		&& line[*i] != '<'
		&& line[*i] != '>'
	)
	{
		if (line[*i] == '\'')
		{
			*quoted = 1;
			word = append_single_quoted(word, line, i);
		}
		else if (line[*i] == '"')
		{
			*quoted = 1;
			word = append_double_quoted(word, line, i);
		}
		else if (line[*i] == '$')
			word = append_variable(word, line, i);
		else
			word = append_plain(word, line, i);
	}
	return (word);
}
