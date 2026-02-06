/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:13:55 by elara-va          #+#    #+#             */
/*   Updated: 2025/04/30 19:03:39 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_null_terminated(char *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (dst[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	original_dst_len;
	size_t	i;
	size_t	j;

	if (size && (!ft_is_null_terminated(dst, size)))
		return (size + ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	original_dst_len = ft_strlen(dst);
	i = original_dst_len;
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (original_dst_len + ft_strlen(src));
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dst[16] = "Hello";
	char src[11] = "! And bye!";
	size_t size = 16;

	printf("Strlen: %zu\n", ft_strlcat(dst, src, size));
	printf("String: %s", dst);
	return (0);
}*/
