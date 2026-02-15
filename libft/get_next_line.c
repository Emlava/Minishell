/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:12:41 by hudescam          #+#    #+#             */
/*   Updated: 2025/10/07 17:49:34 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*f_stock(int fd, char *buffer, char *stock, char stat[BUFFER_SIZE])
{
	ssize_t	count;

	count = 1;
	stock = ft_strdup("");
	if (stat[0] != 0)
		stock = gnl_strjoin(stock, stat);
	while (!gnl_strchr(stock) && count > 0)
	{
		count = read (fd, buffer, BUFFER_SIZE);
		if (count <= 0 && ft_strlen(stock) < 1)
		{
			free(buffer);
			free(stock);
			return (NULL);
		}
		buffer[count] = 0;
		stock = gnl_strjoin(stock, buffer);
	}
	free(buffer);
	return (stock);
}

static char	*extract_stock(char *stock)
{
	char	*str;
	int		i;
	int		y;

	y = -1;
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	str = malloc(sizeof(char) * i + 2);
	if (!str)
	{
		free(stock);
		return (NULL);
	}
	while (++y <= i)
		str[y] = stock[y];
	str[y] = 0;
	return (str);
}

static char	*new_stock(char *stock, char *stat)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
		i++;
	while (stock[i])
		stat[y++] = stock[i++];
	stat[y] = 0;
	free(stock);
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str;
	char		*stock;
	static char	stat[BUFFER_SIZE] = {0};

	stock = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stock = f_stock(fd, buffer, stock, stat);
	if (!stock)
		return (NULL);
	str = extract_stock(stock);
	if (!str)
		return (NULL);
	new_stock(stock, stat);
	return (str);
}

// #include <stdio.h>
// int main ()
// {
// 	int fd;
// 	char *rec;
// 	fd = open("text.txt", O_RDONLY);
// 	int i=0;
// 	while (i < 3)
// 	{
// 		i++;
// 		rec = get_next_line(fd);
// 		printf("%s", rec);
// 		free (rec);
// 	}
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// rec = get_next_line(fd);
// 	// printf("%s", rec);
// 	// free (rec);
// 	// close(fd);
// 	return (0);
// }
