/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:27:52 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:31:43 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*
int main(void)
{
    char str1[] = "Hello, world!";
    char str2[] = "Hello, World!";
    size_t n = 13;

    printf("Input: \"%s\" vs \"%s\", n: %zu\n", str1, str2, n);
    printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, n));
    printf("memcmp:    %d\n", memcmp(str1, str2, n));

    return 0;
}*/