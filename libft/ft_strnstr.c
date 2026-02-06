/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:48:14 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:31:45 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_next_i(size_t i, size_t previous_i)
{
	if (i != previous_i)
		i = previous_i + 1;
	else
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	previous_i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (i < len && big[i])
	{
		previous_i = i;
		while (little[j] == big[i] && i < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + (i - j));
			i++;
			j++;
		}
		i = ft_next_i(i, previous_i);
		j = 0;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	const char *big = "aaabcabcd";
	const char *little = "aabc";
	size_t len = 15;

	if (ft_strnstr(big, little, len) == NULL)
		printf("0\n");
	else
	{
		//printf("%s\n", strnstr(big, little, len));
		//gcc -fsanitize=address -g -w ft_strnstr.c -lbsd
		printf("%s\n", ft_strnstr(big, little, len));
	}
	return (0);
}*/

/*#include <stdio.h>

int	main(void)
{
	const char *big = "ABCDEFGHI";
	const char *little = "DEF";
	size_t len = 9;

	if (ft_strnstr(big, little, len) == NULL)
		printf("0\n");
	else
		printf("%s\n", ft_strnstr(big, little, len));
	return (0);
}*/
