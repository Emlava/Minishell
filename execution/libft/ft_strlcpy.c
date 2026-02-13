/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:29:45 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:30:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (dst == NULL || size == 0)
		return (srclen);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

/*#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char dst[10]; memset(dst, 'A', 10);
	char cpy_dst[10]; memset(cpy_dst, 'A', 10);
	char src[] = "coucou";
	size_t size = 2;

	ft_strlcpy(dst, src, size);
	printf("strlen(src) = %zu\n", strlen(src));
	printf("Destination: %s, Length of Source: %zu\n",
		dst, ft_strlcpy(cpy_dst, src, size));
//	strlcpy(dst, src, size);
//	printf("Destination: %s, Length of Source: %lu\n",
//		dst, strlcpy(cpy_dst, src, size));
	return (0);
}*/
