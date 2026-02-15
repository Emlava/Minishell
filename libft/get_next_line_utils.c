/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:12:38 by hudescam          #+#    #+#             */
/*   Updated: 2025/10/07 17:47:09 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[y])
	{
		str[y] = s1[y];
		y++;
	}
	while (s2[i])
		str[y++] = s2[i++];
	str[y] = 0;
	free ((void *)s1);
	return (str);
}

char	*gnl_strchr(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	if (*s == '\n')
		return ((char *)s);
	return (NULL);
}
