/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:15:33 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:55 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;

	ptr = (unsigned char *)s;
	value = (unsigned char)c;
	while (n)
	{
		*ptr = value;
		ptr++;
		n--;
	}
	return (s);
}

/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	char s1[] = "ABCDEFGHI";
	char s2[] = "ABCDEFGHI";
	char c = '*';
	int n = 3;

	ft_memset(s1, c, n);
	memset(s2, c, n);
	printf("%s\n%s\n", s1, s2);
	return (0);
}*/
