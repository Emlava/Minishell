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

static int	ft_ishexalpha(int c)
{
	if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
		return (1);
	else
		return (0);
}

static void	ft_convert_char(char c, long *result)
{
	if (ft_isdigit(c))
		*result = *result * 16 + (c - '0');
	else if (c >= 'A' && c <= 'F')
		*result = *result * 16 + ((c - 'A') + 10);
	else
		*result = *result * 16 + ((c - 'a') + 10);
	return ;
}

int	ft_hexatoi(const char *nptr)
{
	size_t	i;
	int		minus;
	long	result;

	minus = 0;
	result = 0;
	i = ft_if_space_or_sign(nptr);
	if (i && nptr[i - 1] == '-')
		minus = 1;
	if ((nptr[i] == '0' && (nptr[i + 1]) == 'X') || nptr[i + 1] == 'x')
		i += 2;
	else
		return (0);
	if (!ft_isdigit(nptr[i]) && !ft_ishexalpha(nptr[i]))
		return (0);
	while (ft_isdigit(nptr[i]) || ft_ishexalpha(nptr[i]))
	{
		ft_convert_char(nptr[i], &result);
		i++;
	}
	if (minus)
		result = -result;
	return ((int)result);
}

/*
int	main(int ac, char *av[])
{
	if (ac != 2)
		return (1);
	ft_printf("%d\n", ft_hexatoi(av[1]));
	return (0);
}
*/
