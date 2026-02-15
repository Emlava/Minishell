/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:42:34 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:26:55 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (s2[0] == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		y = 0;
		while (s1[i + y] == s2[y] && s1[i + y] && i + y < len)
			y++;
		if (s2[y] == 0)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}

/*int main(void)
{
    const char haystack[] = "Hello, world!";
    const char needle[] = "world";
    size_t len = 13;

    printf("Input: \"%s\", Needle: \"%s\", len: %zu\n", haystack, needle, len);
    printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, len));
    printf("strnstr:    %s\n", strnstr(haystack, needle, len));

    return 0;
}*/