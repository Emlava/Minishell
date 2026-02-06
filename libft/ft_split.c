/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:42 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:27:38 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_substrlen(const char *s, const char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_cpy(const char *s1, char *s2, char c)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (i);
}

static void	ft_freeing(size_t j, char **array)
{
	if (!j)
	{
		free(array);
		return ;
	}
	j--;
	while (j > 0)
	{
		free(array[j]);
		j--;
	}
	free(array[j]);
	free(array);
}

static char	**ft_chop(char const *s, char c, char **array)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		array[j] = malloc(ft_substrlen(s + i, c) + 1);
		if (!array[j])
		{
			ft_freeing(j, array);
			return (NULL);
		}
		k = ft_cpy(&s[i], array[j], c);
		i += k;
		j++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**array;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	array = malloc(sizeof(char *) * (j + 1));
	if (!array)
		return (NULL);
	return (ft_chop(s, c, array));
}

/*#include <stdio.h>

int	main(void)
{
	char const *s = "chinimala,,,,dh,,,hgm,f,";
	char c = ',';
	char **array;
	int i = 0;

	array = ft_split(s, c);
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return (0);
}*/
