/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:26:36 by hudescam          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:18 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	def_type(char c, va_list var)
{
	int	nbr;

	nbr = 0;
	if (c == 'c')
		nbr = ft_inputchar(va_arg(var, int));
	else if (c == 's')
		nbr = ft_inputstr(va_arg(var, char *));
	else if (c == 'p')
		nbr = ft_inputpoint(va_arg(var, void *));
	else if (c == 'd' || c == 'i')
		nbr = ft_inputnbr(va_arg(var, int));
	else if (c == 'u')
		nbr = ft_inputunsid(va_arg(var, unsigned int));
	else if (c == 'x')
		nbr = ft_inputhexa(va_arg(var, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		nbr = ft_inputhexa(va_arg(var, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		nbr = ft_inputchar('%');
	return (nbr);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		nbr_char;
	va_list	var;

	i = 0;
	nbr_char = 0;
	va_start(var, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			nbr_char += def_type(str[i], var);
		}
		else
			nbr_char += ft_inputchar(str[i]);
		i++;
	}
	va_end(var);
	return (nbr_char);
}
