/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:34:50 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:26:37 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_zero_or_low(int n, int fd)
{
	char	*str;

	if (n == 0)
		write(fd, "0", 1);
	else
	{
		str = "-2147483648";
		write(fd, str, 11);
	}
}

static int	ft_nbr_to_char(int n, size_t i, char inv_str[], char str[])
{
	size_t	j;

	j = 0;
	while (n > 0)
	{
		inv_str[j] = (n % 10) + '0';
		j++;
		n /= 10;
	}
	j -= 1;
	while (j > 0)
	{
		str[i] = inv_str[j];
		i++;
		j--;
	}
	str[i] = inv_str[j];
	i++;
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	char	inv_str[12];
	size_t	i;

	if (n == 0 || n == -2147483648)
	{
		ft_zero_or_low(n, fd);
		return ;
	}
	i = 0;
	if (n < 0)
	{
		n = -n;
		str[i] = '-';
		i++;
	}
	i = ft_nbr_to_char(n, i, inv_str, str);
	write(fd, str, i);
}

/*int	main(void)
{
	int n = -123;
	int fd = 1;

	ft_putnbr_fd(n, fd);
	write(fd, "\n", 1);
	return (0);
}*/
