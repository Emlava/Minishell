/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:39:19 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

/*int main(void)
{
    char str1[10] = "abcdef";
    char str2[10] = "abcdef";

    ft_bzero(str1, 3);

    bzero(str2, 3);

    printf("ft_bzero: \"%s\"\n", str1);
    printf("bzero:    \"%s\"\n", str2);

    return 0;
}*/