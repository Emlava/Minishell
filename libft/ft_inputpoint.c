/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputpoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:29:10 by hudescam          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:07 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_inputpoint(void *point)
{
	unsigned long	point2;

	point2 = (unsigned long) point;
	if (point == 0)
		return (ft_inputstr("(nil)"));
	return (ft_inputstr("0x") + ft_inputhexa(point2, "0123456789abcdef"));
}
