/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:58:20 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:29:09 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	i;

	new_s = malloc(ft_strlen(s) + 1);
	i = 0;
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

/*#include <stdio.h>

int	main(void)
{
	const char *s = "Hello!";

	printf("s: \"%s\", new_s: \"%s\"\n", s, ft_strdup(s));
	return (0);
}*/
