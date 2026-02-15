/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:01:39 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/13 15:42:47 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_word(char const *s, char c)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			nbr++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nbr);
}

static int	nbr_letter(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	free_tab(char **tab, int y)
{
	int	t;

	t = 0;
	while (t <= y)
	{
		free(tab[t]);
		t++;
	}
	free(tab);
}

static char	**fill_tab(char const *s, char c, char **tab)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			tab[y] = ft_calloc(nbr_letter(s + i, c) + 1, sizeof(char));
			if (tab[y] == NULL)
			{
				free_tab(tab, y);
				return (NULL);
			}
			ft_strlcpy(tab[y], s + i, nbr_letter(s + i, c) + 1);
			y++;
			i += nbr_letter(s + i, c);
		}
	}
	tab [y] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(nbr_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (fill_tab(s, c, tab));
}

/*int main(void)
{
    char **result;
    char str[] = "Hello world this is libft";
    char delimiter = ' ';
	int i = 0;

    result = ft_split(str, delimiter);
    while (result[i] != NULL)
    {
        printf("Word %d: %s\n", i, result[i]);
		i++;
    }
    free_tab(result, i);

    return 0;
}*/