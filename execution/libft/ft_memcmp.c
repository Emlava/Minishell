/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:28:33 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:22:43 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n && *p1 == *p2)
	{
		p1++;
		p2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*p1 - (unsigned char)*p2);
}

/*#include <stdio.h>

int	main(void)
{
	const char *s1 = "ABD";
	const char *s2 = "ABC";
	int n = 3;

	printf("Difference between \"%s\" and \"%s\" up to char %d: %d\n",
		s1, s2, n, ft_memcmp(s1, s2, n));
	return (0);
}*/
