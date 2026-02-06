/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:35:33 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:28:00 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && (unsigned char)*s != (unsigned char)c)
		s++;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	else
		return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	char *s = "ABCDEFGHI";
	int c = 'C';

	if (ft_strchr(s, c) != NULL)
		printf("%s\n", ft_strchr(s, c));
	else
		printf("0\n");
	return (0);
}*/
