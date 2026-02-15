/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:10:25 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (s);
}

/*int main(void)
{
    char str1[20] = "Hello, world!";
    char str2[20] = "Hello, world!";

    printf("Before memset:\n");
    printf("ft_memset: \"%s\"\n", str1);
    printf("memset:    \"%s\"\n", str2);

    ft_memset(str1, '*', 5);
    memset(str2, '*', 5);

    printf("After memset:\n");
    printf("ft_memset: \"%s\"\n", str1);
    printf("memset:    \"%s\"\n", str2);

    return 0;
}*/