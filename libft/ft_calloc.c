/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:57:33 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/09 15:17:16 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;

	if (size != 0 && nmemb > ((size_t)-1) / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, nmemb * size);
	return (mem);
}

/*int main(void)
{
    size_t nmemb = 5;
    size_t size = sizeof(int);

    int *arr1 = (int *)ft_calloc(nmemb, size);

    int *arr2 = (int *)calloc(nmemb, size);

    if (arr1 && arr2)
    {
        printf("ft_calloc: ");
        for (size_t i = 0; i < nmemb; i++)
            printf("%d ", arr1[i]);
        printf("\n");

        printf("calloc:    ");
        for (size_t i = 0; i < nmemb; i++)
            printf("%d ", arr2[i]);
        printf("\n");
    }

    free(arr1);
    free(arr2);

    return 0;
}*/