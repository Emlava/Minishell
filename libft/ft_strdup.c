/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:40:41 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:30 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	i;

	i = 0;
	d = malloc(ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

/*int main(void)
{
    const char str[] = "Hello, world!";
    char *dup;

    dup = ft_strdup(str);
    if (dup)
    {
        printf("Original: \"%s\"\n", str);
        printf("Duplicate: \"%s\"\n", dup);
        free(dup);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/