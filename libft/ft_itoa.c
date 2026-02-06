/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:30:45 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:21:52 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static char	*ft_zero_or_lower_limit(int n, char *s_lowerlimit)
{
	char	*str;
	size_t	i;

	if (n == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	i = 0;
	while (s_lowerlimit[i])
	{
		str[i] = s_lowerlimit[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_allocation(int n, int negative)
{
	char	*str;
	size_t	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		if (n == 0)
			i += 2;
		else
			i++;
	}
	if (negative == 1)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_nbr_to_char(char *invstr, char *str, int n, int negative)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		invstr[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	i -= 1;
	j = 0;
	if (negative == 1)
	{
		str[j] = '-';
		j++;
	}
	while (i > 0)
		str[j++] = invstr[i--];
	str[j++] = invstr[i];
	str[j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	invstr[10];
	char	*s_lowerlimit;
	int		negative;

	if (n == 0 || n == -2147483648)
	{
		s_lowerlimit = "-2147483648";
		return (ft_zero_or_lower_limit(n, s_lowerlimit));
	}
	negative = 0;
	if (n < 0)
	{
		n = -n;
		negative = 1;
	}
	return (ft_nbr_to_char(invstr, ft_allocation(n, negative), n, negative));
}

/*#include <stdio.h>

int	main(void)
{
	int n = -123;

	printf("%s\n", ft_itoa(n));
	return (0);
}*/
