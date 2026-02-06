/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csu_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:00:22 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/19 15:14:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_d_c(int fd, unsigned char c)
{
	int	new_char;

	write(fd, &c, 1);
	new_char = 1;
	return (new_char);
}

int	ft_d_s(int fd, const char *s)
{
	int	new_chars;

	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	ft_putstr_fd((char *)s, fd);
	new_chars = (int)ft_strlen(s);
	return (new_chars);
}

int	ft_d_u(int fd, unsigned int u)
{
	char	u_int[11];
	size_t	local_i;
	int		new_chars;

	if (u == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	local_i = 0;
	while (u > 0)
	{
		u_int[local_i] = (u % 10) + '0';
		local_i++;
		u /= 10;
	}
	new_chars = (int)local_i;
	local_i -= 1;
	while (local_i)
	{
		write(fd, &u_int[local_i], 1);
		local_i--;
	}
	write(fd, &u_int[local_i], 1);
	return (new_chars);
}

int	ft_d_percent(int fd)
{
	int	new_char;

	write(fd, "%", 1);
	new_char = 1;
	return (new_char);
}
