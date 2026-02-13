/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:15:54 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:22:11 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		chr;

	if (n == 0)
		return (NULL);
	p = (const unsigned char *)s;
	chr = (unsigned char)c;
	while (n > 1 && *p != chr)
	{
		n--;
		p++;
	}
	if (*p == chr)
		return ((void *)p);
	else
		return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	const char *s = "ABCEFGHI";
	char	c = 'I';
	size_t n = 5;

	if (ft_memchr(s, c, n) == NULL)
		printf("0\n");
	else
		printf("%s\n", (char *)ft_memchr(s, c, n));
	return (0);
}*/
