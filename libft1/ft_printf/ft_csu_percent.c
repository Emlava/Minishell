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

#include "ft_printf.h"

int	ft_c(unsigned char c)
{
	int	new_char;

	write(1, &c, 1);
	new_char = 1;
	return (new_char);
}

int	ft_s(const char *s)
{
	int	new_chars;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd((char *)s, 1);
	new_chars = (int)ft_strlen(s);
	return (new_chars);
}

int	ft_u(unsigned int u)
{
	char	u_int[11];
	size_t	local_i;
	int		new_chars;

	if (u == 0)
	{
		write(1, "0", 1);
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
		write(1, &u_int[local_i], 1);
		local_i--;
	}
	write(1, &u_int[local_i], 1);
	return (new_chars);
}

int	ft_percent(void)
{
	int	new_char;

	write(1, "%", 1);
	new_char = 1;
	return (new_char);
}
