/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:21:37 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:26:55 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/*int main(void)
{
    char c = 'A';

    printf("Input: '%c'\n", c);
    printf("ft_tolower: '%c'\n", ft_tolower(c));
    printf("tolower:    '%c'\n", tolower(c));

    return 0;
}*/