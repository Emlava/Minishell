/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:47:27 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/02 18:28:20 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

/*void	ft_tozero(unsigned int i, char *s)
{
	if (i > 2)
		*s = '0';
}

#include <stdio.h>

int	main(void)
{
	char s[] = "ABCDEFGHI";

	printf("\"%s\" ", s);
	ft_striteri(s, ft_tozero);
	printf("becomes \"%s\"\n", s);
	return (0);
}*/
