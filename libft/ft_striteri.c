/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:59:02 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}

/*void example_function(unsigned int i, char *c)
{
    *c = *c + i; // Modifie chaque caractère en fonction de son index
}

int main(void)
{
    char str[] = "Hello";

    printf("Before: %s\n", str);
    ft_striteri(str, example_function);
    printf("After: %s\n", str);

    return 0;
}*/