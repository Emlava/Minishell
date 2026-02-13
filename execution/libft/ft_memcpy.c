/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:44:37 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:06 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (n--)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest[] = "000000000";
	char src[] = "ABCDEFGHI";
	int n = 3;

	printf("%s\n",(char *)ft_memcpy(dest, src, n));
	printf("%s\n",(char *)memcpy(dest, src, n));
	return (0);
}*/
