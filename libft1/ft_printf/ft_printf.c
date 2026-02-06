/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:14:53 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/19 17:39:40 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_flag_parsing(const char **format)
{
	int	f_space;
	int	f_plus;
	int	f_nbr_sign;

	f_space = 0;
	f_plus = 0;
	f_nbr_sign = 0;
	while (**format == ' ' || **format == '+'
		|| **format == '#')
	{
		if (**format == ' ')
			f_space = 1;
		else if (**format == '+')
			f_plus = 2;
		else if (**format == '#')
			f_nbr_sign = 4;
		(*format)++;
	}
	return (f_space + f_plus + f_nbr_sign);
}

static int	ft_format_specifier(const char **format, va_list ap)
{
	int	new_chars;
	int	flags;

	(*format)++;
	new_chars = 0;
	flags = ft_flag_parsing(format);
	if (**format == 'c')
		new_chars = ft_c((unsigned char)va_arg(ap, int));
	else if (**format == 's')
		new_chars = ft_s(va_arg(ap, const char *));
	else if (**format == 'p')
		new_chars = ft_p(va_arg(ap, void *));
	else if (**format == 'd' || **format == 'i')
		new_chars = ft_d_i(va_arg(ap, int), flags);
	else if (**format == 'u')
		new_chars = ft_u(va_arg(ap, unsigned int));
	else if (**format == 'x' || **format == 'X')
		new_chars = ft_xx(format, va_arg(ap, unsigned int), flags);
	else if (**format == '%')
		new_chars = ft_percent();
	else
		return (0);
	(*format)++;
	return (new_chars);
}

static	int	ft_print_literal_chars(const char **format)
{
	int	new_chars;

	new_chars = 0;
	while (**format && **format != '%')
	{
		write(1, *format, 1);
		(*format)++;
		new_chars++;
	}
	return (new_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		printed_chars;

	if (!format)
		return (-1);
	va_start(ap, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format != '%')
			printed_chars += ft_print_literal_chars(&format);
		if (*format == '%')
		{
			if (!*(format + 1))
			{
				va_end(ap);
				return (-1);
			}
			printed_chars += ft_format_specifier(&format, ap);
		}
	}
	va_end(ap);
	return (printed_chars);
}
