/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:22:35 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:32 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_if_space_or_sign(const char *nptr)
{
	size_t	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		minus;
	long	result;

	minus = 0;
	result = 0;
	i = ft_if_space_or_sign(nptr);
	if (i && nptr[i - 1] == '-')
		minus = 1;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (minus)
		result = -result;
	return ((int)result);
}

/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
 {
	const char	*test = "-1";
	const char	*nptr1 = &test[1];
	const char	*test2 = "-12-23";
	const char	*nptr2 = &test2[1];

	printf("%d\n", atoi(nptr1));
	printf("%d\n", ft_atoi(nptr1));
	printf("%d\n", atoi(nptr2));
	printf("%d\n", ft_atoi(nptr2));
	return (0);
}*/

/*int	main(void)
{
	const char *nptr = "-123";

	printf("%d\n", atoi(nptr));
	printf("%d\n", ft_atoi(nptr));
	return (0);
}*/
