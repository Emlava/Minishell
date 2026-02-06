/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:05:30 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/03 16:54:41 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

static char	*ft_allocation(size_t i, size_t start_s2, char const *s1)
{
	char	*s2;

	if (i == start_s2)
		s2 = malloc(sizeof(char) * 2);
	else
		s2 = malloc(sizeof(char)
				* ((ft_strlen(s1 + start_s2) - ft_strlen(s1 + (i + 1))) + 1));
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start_s2;
	size_t	j;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	while (ft_is_set(s1[i], set))
		i++;
	start_s2 = i;
	while (s1[i + 1])
		i++;
	while (ft_is_set(s1[i], set) && i > start_s2)
		i--;
	s2 = ft_allocation(i, start_s2, s1);
	if (!s2)
		return (NULL);
	j = 0;
	while (start_s2 <= i)
		s2[j++] = s1[start_s2++];
	s2[j] = '\0';
	return (s2);
}

/*#include <stdio.h>

int	main(void)
{
	char *s1 = "AABCDEFGHII";
	char *set = "ABI";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
