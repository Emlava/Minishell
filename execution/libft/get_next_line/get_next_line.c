/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:10:08 by elara-va          #+#    #+#             */
/*   Updated: 2025/06/03 20:53:33 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	manage_buf(char *buf)
{
	ssize_t	buf_nl_index;

	buf_nl_index = find_nl(buf);
	if (buf[buf_nl_index + 1] == '\0')
		buf[0] = '\0';
	else
		cpy_buf_to_buf(buf, &buf[buf_nl_index + 1]);
}

static char	*extend_line(char *buf, char *line)
{
	char	*next_part_of_line;

	next_part_of_line = malloc(sizeof(char) * strlen_nl(buf) + 1);
	if (!next_part_of_line)
	{
		free(line);
		return (NULL);
	}
	cpy_buf_to_line(next_part_of_line, buf);
	line = strjoin_free(line, next_part_of_line);
	return (line);
}

static	char	*create_line_to_return(char *buf, int fd,
		ssize_t chars_in_buf)
{
	char	*line;

	line = malloc(sizeof(char) * strlen_nl((const char *)buf) + 1);
	if (!line)
		return (NULL);
	cpy_buf_to_line(line, buf);
	while (find_nl(line) < 0)
	{
		chars_in_buf = read(fd, buf, BUFFER_SIZE);
		if (chars_in_buf < 0)
		{
			free(line);
			return (NULL);
		}
		if (chars_in_buf == 0)
		{
			buf[0] = '\0';
			return (line);
		}
		buf[chars_in_buf] = '\0';
		line = extend_line(buf, line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		chars_in_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	chars_in_buf = 0;
	if (!buf[0])
	{
		chars_in_buf = read(fd, buf, BUFFER_SIZE);
		if (chars_in_buf <= 0)
			return (NULL);
		buf[chars_in_buf] = '\0';
	}
	line = create_line_to_return(buf, fd, chars_in_buf);
	manage_buf(buf);
	return (line);
}
