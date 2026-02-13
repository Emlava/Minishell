/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:09:09 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:27 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}

/*#include <stdio.h>

int	main(void)
{
	char s[] = "ABCDEFGHI";
	int n = 3;

	ft_bzero(s, n);
	printf("%s\n", s + n);
	return (0);
}*/
