/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputunsid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:30:16 by hudescam          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:14 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_inputunsid(unsigned int deci)
{
	int	nbr;

	nbr = 0;
	if (deci > 9)
	{
		nbr += ft_inputunsid(deci / 10);
		nbr += ft_inputunsid(deci % 10);
	}
	else
		nbr += ft_inputchar(deci + '0');
	return (nbr);
}
