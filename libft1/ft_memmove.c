/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:58:23 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:32 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if ((unsigned char *)dest < (unsigned char *)src)
	{
		ptr1 = (unsigned char *)dest;
		ptr2 = (unsigned char *)src;
		while (n--)
			*ptr1++ = *ptr2++;
	}
	else
	{
		ptr1 = (unsigned char *)dest + (n - 1);
		ptr2 = (unsigned char *)src + (n - 1);
		while (n--)
			*ptr1-- = *ptr2--;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[100] = "ABCDEFGHI";
	char *dest_src = str;
	int n = 3;

	ft_memmove(dest_src + 3, dest_src, n);
	printf("%s\n", str);
	return (0);
}*/
