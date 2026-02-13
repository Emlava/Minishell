/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:42:30 by elara-va          #+#    #+#             */
/*   Updated: 2025/06/03 19:52:45 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	cpy_buf_to_buf(char *new_buf, char *old_buf)
{
	size_t	i;

	i = 0;
	while (old_buf[i])
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	new_buf[i] = '\0';
}

char	*strjoin_free(char *line, char *next_part_of_line)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = malloc(sizeof(char) * (strlen_nl(line)
				+ strlen_nl(next_part_of_line) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
		new_str[j++] = line[i++];
	i = 0;
	while (next_part_of_line[i])
		new_str[j++] = next_part_of_line[i++];
	new_str[j] = '\0';
	free(line);
	free(next_part_of_line);
	return (new_str);
}

ssize_t	find_nl(char *buf)
{
	size_t	nl_index;

	nl_index = 0;
	while (buf[nl_index])
	{
		if (buf[nl_index] == '\n')
			return (nl_index);
		nl_index++;
	}
	return (-1);
}

void	cpy_buf_to_line(char *line, char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		line[i] = buf[i];
		if (buf[i] == '\n')
		{
			i++;
			break ;
		}
		else
			i++;
	}
	line[i] = '\0';
}

size_t	strlen_nl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		else
			i++;
	}
	return (i);
}
