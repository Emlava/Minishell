/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:24:49 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:31:17 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*p1;
	unsigned const char	*p2;

	p1 = (unsigned const char *)s1;
	p2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (*p1 && *p1 == *p2 && n > 1)
	{
		p1++;
		p2++;
		n--;
	}
	return (*p1 - *p2);
}

/*#include <stdio.h>

int	main(void)
{
	const char *s1 = "ABD";
	const char *s2 = "ABC";
	int n = 3;

	printf("Difference between \"%s\" and \"%s\" up to char %d: %d\n",
		s1, s2, n, ft_strncmp(s1, s2, n));
	return (0);
}*/
