/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:40:34 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:26:55 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		y;

	if (!s1 || !set)
		return (NULL);
	y = ft_strlen(s1)-1;
	i = 0;
	if (*s1 == 0)
		return (ft_strdup(""));
	while (is_in(s1[i], set))
		i++;
	if (i > y)
		return (ft_strdup(""));
	while (is_in(s1[y], set))
		y--;
	str = ft_substr(s1, i, y - i + 1);
	return (str);
}

/*int main(void)
{
    const char s1[] = "   Hello, world!   ";
    const char set[] = " ";

    char *result = ft_strtrim(s1, set);
    if (result)
    {
        printf("Original: \"%s\"\n", s1);
        printf("Trimmed:  \"%s\"\n", result);
        free(result);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/