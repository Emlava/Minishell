/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:21:57 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	if (ptrsrc < ptrdest && ptrdest < ptrsrc + n)
	{
		ptrsrc += n;
		ptrdest += n;
		while (n--)
			*(--ptrdest) = *(--ptrsrc);
	}
	else
	{
		while (n--)
			*ptrdest++ = *ptrsrc++;
	}
	return (dest);
}

/*int main(void)
{
    char src[] = "Hello, world!";
    char dest1[20] = "Test";
    char dest2[20] = "Test";

    printf("Before memmove:\n");
    printf("ft_memmove dest: \"%s\"\n", dest1);
    printf("memmove dest:    \"%s\"\n", dest2);

    ft_memmove(dest1, src, 13);
    memmove(dest2, src, 13);

    printf("After memmove:\n");
    printf("ft_memmove dest: \"%s\"\n", dest1);
    printf("memmove dest:    \"%s\"\n", dest2);

    return 0;
}*/