/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:11:26 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	ch;

	str = (unsigned char *) s;
	i = 0;
	ch = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

/*int main(void)
{
    char str[] = "Hello, world!";
    char c = 'w';
    size_t n = 13;

    printf("Input: \"%s\", Char: '%c', n: %zu\n", str, c, n);
    printf("ft_memchr: %s\n", (char *)ft_memchr(str, c, n));
    printf("memchr:    %s\n", (char *)memchr(str, c, n));

    return 0;
}*/