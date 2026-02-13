/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:22 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/03 17:38:40 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;

	if (!s)
		return (NULL);
	newstr = malloc(ft_strlen(s) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

/*static char	ft_toupperifodd(unsigned int i, char c)
{
	if ((i == 0 || i % 2 == 0) && (c >= 97 && c <= 122))
		return (c - 32);
	else
		return (c);
}

#include <stdio.h>

int	main(void)
{
	char const *s = "abcdefghi";

	printf("\"%s\" becomes \"%s\"\n", s, ft_strmapi(s, ft_toupperifodd));
	return (0);
}*/
