/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:56:51 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:13:33 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_of_int(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*create_char(char *nbr, int count, int n)
{
	nbr[count] = 0;
	count--;
	if (n == 0)
		nbr[0] = '0';
	if (n < 0)
	{
		nbr[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		nbr[count] = '0' + (n % 10);
		n = n / 10;
		count--;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		count;
	int		sign;
	char	*nbr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
	}
	count = nbr_of_int(n) + sign;
	nbr = malloc((count + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	return (create_char(nbr, count, n));
}

/*int main(void)
{
    int n = -12345;

    printf("Input: %d\n", n);
    printf("ft_itoa: %s\n", ft_itoa(n));

    return 0;
}*/