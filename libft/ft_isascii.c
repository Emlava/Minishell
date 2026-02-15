/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:35:25 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int main(void)
{
    char c = 127;

    printf("Char: '%c' (ASCII: %d)\n", c, c);
    printf("ft_isascii: %d\n", ft_isascii(c));
    printf("isascii:    %d\n", isascii(c));

    return 0;
}*/