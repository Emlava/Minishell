/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:16:56 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:26:25 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/*int main(void)
{
    char c = 'a';

    printf("Input: '%c'\n", c);
    printf("ft_toupper: '%c'\n", ft_toupper(c));
    printf("toupper:    '%c'\n", toupper(c));

    return 0;
}*/