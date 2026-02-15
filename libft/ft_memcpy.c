/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:55:59 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:29:59 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	while (n--)
		*ptrdest++ = *ptrsrc++;
	return (dest);
}

/*int main(void)
{
    char str1[] = "Hello, world!";
    char str2[] = "Hello, World!";
    size_t n = 13;

    printf("Input: \"%s\" vs \"%s\", n: %zu\n", str1, str2, n);
    printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, n));
    printf("memcmp:    %d\n", memcmp(str1, str2, n));

    return 0;
}*/