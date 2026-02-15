/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:37:44 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:26:55 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*checkp;
	char	d;

	checkp = NULL;
	d = (char)c;
	while (*s)
	{
		if (*s == d)
			checkp = (char *)s;
		s++;
	}
	if (*s == d)
		checkp = (char *)s;
	return (checkp);
}

/*int main(void)
{
    const char str[] = "Hello, world!";
    char c = 'o';

    printf("Input: \"%s\", Char: '%c'\n", str, c);
    printf("ft_strrchr: %s\n", ft_strrchr(str, c));
    printf("strrchr:    %s\n", strrchr(str, c));

    return 0;
}*/