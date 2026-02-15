/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:55:12 by hudescam          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:03 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(int n)
{
	int	i;

	i = 1;
	if (n > 0)
		i--;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_inputnbr(int n)
{
	char	c;

	if (n == -2147483648)
		write (1, "-2147483648", 11);
	else if (n < 0)
	{
		write (1, "-", 1);
		ft_inputnbr(-n);
	}
	else
	{
		if (n > 9)
		{
			ft_inputnbr(n / 10);
			ft_inputnbr(n % 10);
		}
		else
		{
			c = n + 48;
			write (1, &c, 1);
		}
	}
	return (count_numbers(n));
}
