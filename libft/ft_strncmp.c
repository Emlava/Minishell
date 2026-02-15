/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:45:44 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

/*int main(void)
{
    const char s1[] = "Hello";
    const char s2[] = "HelLo";
    size_t n = 3;

    printf("Input: \"%s\" vs \"%s\", n: %zu\n", s1, s2, n);
    printf("ft_strncmp: %d\n", ft_strncmp(s1, s2, n));
    printf("strncmp:    %d\n", strncmp(s1, s2, n));

    return 0;
}*/