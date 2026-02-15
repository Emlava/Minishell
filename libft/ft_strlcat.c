/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:12:58 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dsize)
		return (dsize + srclen);
	if (srclen < dsize - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dst + dstlen, src, dsize - dstlen - 1);
		dst[dsize - 1] = 0;
	}
	return (dstlen + srclen);
}

/*int main(void)
{
    char dst1[20] = "Hello, ";
    char dst2[20] = "Hello, ";
    const char src[] = "world!";
    size_t dsize = 20;

    printf("Before:\n");
    printf("ft_strlcat: \"%s\"\n", dst1);
    printf("strlcat:    \"%s\"\n", dst2);

    ft_strlcat(dst1, src, dsize);
    strlcat(dst2, src, dsize);

    printf("After:\n");
    printf("ft_strlcat: \"%s\"\n", dst1);
    printf("strlcat:    \"%s\"\n", dst2);

    return 0;
}*/