/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:06:17 by hudescam          #+#    #+#             */
/*   Updated: 2025/05/13 16:48:59 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	create_nbr(size_t nbr, int i, int sign, const char *str)
{
	size_t	max;

	while (ft_isdigit(str[i]))
	{
		max = nbr;
		nbr = nbr * 10 + (str[i] - '0');
		if (max > nbr && sign == 1)
			return (-1);
		if (max > nbr && sign == -1)
			return (0);
		i++;
	}
	nbr = nbr * sign;
	return (nbr);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	nbr;
	int		i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nbr = create_nbr(nbr, i, sign, str);
	return ((int)nbr);
}

/*int main(void)
{
    const char *str = "   265415";
    printf("Input: \"%s\"\n", str);
    printf("ft_atoi: %d\n", ft_atoi(str));
    printf("atoi:    %d\n", atoi(str));
    return 0;
}*/