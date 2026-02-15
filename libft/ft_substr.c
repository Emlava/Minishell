/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:39:32 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:25:37 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if ((len_s - start) < len)
		len = len_s - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

/*int main(void)
{
    const char s[] = "Hello, world!";
    unsigned int start = 7;
    size_t len = 5;

    char *result = ft_substr(s, start, len);
    if (result)
    {
        printf("Original: \"%s\"\n", s);
        printf("Substring: \"%s\"\n", result);
        free(result);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/