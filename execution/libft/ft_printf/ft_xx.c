/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:17:16 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/19 18:49:32 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_flag(const char **format, int flags)
{
	int	new_chars;

	new_chars = 0;
	if (flags >= 4)
	{
		new_chars = 2;
		if (**format == 'x')
			write(1, "0x", 2);
		else if (**format == 'X')
			write(1, "0X", 2);
	}
	return (new_chars);
}

static int	ft_printing(unsigned int xx, int to_char)
{
	size_t	i;
	char	hex_str[9];
	int		new_chars;

	i = 0;
	while (xx > 0)
	{
		if (xx % 16 > 9)
			hex_str[i] = (xx % 16) + to_char;
		else
			hex_str[i] = (xx % 16) + '0';
		xx /= 16;
		i++;
	}
	new_chars = (int)i;
	i -= 1;
	while (i)
	{
		write(1, &hex_str[i], 1);
		i--;
	}
	write(1, &hex_str[i], 1);
	return (new_chars);
}

int	ft_xx(const char **format, unsigned int xx, int flags)
{
	int		new_chars;
	int		to_char;

	to_char = 0;
	if (xx == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	new_chars = ft_flag(format, flags);
	if (**format == 'x')
		to_char = 87;
	else if (**format == 'X')
		to_char = 55;
	new_chars += ft_printing(xx, to_char);
	return (new_chars);
}
