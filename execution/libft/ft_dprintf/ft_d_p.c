/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:23:52 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/18 14:31:30 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	ft_printing(int fd, char *hex_str, size_t local_i)
{
	while (local_i)
	{
		write(fd, &hex_str[local_i], 1);
		local_i--;
	}
	write(1, &hex_str[local_i], 1);
}

static int	ft_null_p(int fd)
{
	write(fd, "(nil)", 5);
	return (5);
}

int	ft_d_p(int fd, void *p)
{
	int			new_chars;
	uintptr_t	decimal_address;
	size_t		local_i;
	char		hex_str[17];

	if (p == NULL)
		return (ft_null_p(fd));
	write(fd, "0x", 2);
	new_chars = 2;
	local_i = 0;
	decimal_address = (uintptr_t)p;
	while (decimal_address > 0)
	{
		if (decimal_address % 16 > 9)
			hex_str[local_i] = (decimal_address % 16) + 87;
		else
			hex_str[local_i] = (decimal_address % 16) + '0';
		decimal_address /= 16;
		local_i++;
	}
	new_chars += (int)local_i;
	local_i -= 1;
	ft_printing(fd, hex_str, local_i);
	return (new_chars);
}
