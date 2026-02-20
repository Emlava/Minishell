/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:57:34 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/23 12:25:02 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_flag_management(int fd, int d_i, int flags)
{
	int	new_chars;

	new_chars = 0;
	if (d_i >= 0)
	{
		if (flags == 1 || flags == 5)
		{
			write(fd, " ", 1);
			new_chars++;
		}
		else if (flags == 2 || flags == 3 || flags == 6 || flags == 7)
		{
			write(fd, "+", 1);
			new_chars++;
		}
	}
	return (new_chars);
}

int	ft_d_di(int fd, int d_i, int flags)
{
	int	new_chars;

	new_chars = ft_flag_management(fd, d_i, flags);
	ft_putnbr_fd(d_i, fd);
	if (d_i == 0)
		new_chars += 1;
	else if (d_i == INT_MIN)
		new_chars = 11;
	else
	{
		if (d_i < 0)
		{
			new_chars++;
			d_i = -d_i;
		}
		while (d_i >= 1)
		{
			d_i /= 10;
			new_chars++;
		}
	}
	return (new_chars);
}
