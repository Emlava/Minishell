/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:11:54 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dsize)
		ft_memcpy(dst, src, srclen + 1);
	else if (dsize != 0)
	{
		ft_memcpy(dst, src, dsize - 1);
		dst[dsize - 1] = 0;
	}
	return (srclen);
}

/*int main(void)
{
    char dst1[20];
    char dst2[20];
    const char src[] = "Hello, world!";
    size_t dsize = 10;

    printf("Source: \"%s\"\n", src);

    ft_strlcpy(dst1, src, dsize);
    strlcpy(dst2, src, dsize);

    printf("ft_strlcpy: \"%s\"\n", dst1);
    printf("strlcpy:    \"%s\"\n", dst2);

    return 0;
}*/