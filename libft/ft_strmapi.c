/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyobo <kyobo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:57:44 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/13 11:57:48 by kyobo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	unsigned int	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}

/*char example_function(unsigned int i, char c)
{
    return c + i; // Modifie chaque caractère en fonction de son index
}

int main(void)
{
    const char str[] = "Hello";
    char *result;

    result = ft_strmapi(str, example_function);
    if (result)
    {
        printf("Original: %s\n", str);
        printf("Modified: %s\n", result);
        free(result);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/