/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:31:07 by hudescam          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:00 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_inputhexa(unsigned long deci, char *base)
{
	int	nbr;

	nbr = 0;
	if (deci > 15)
	{
		nbr += ft_inputhexa(deci / 16, base);
		nbr += ft_inputhexa(deci % 16, base);
	}
	else
		nbr += ft_inputchar(base[deci]);
	return (nbr);
}
