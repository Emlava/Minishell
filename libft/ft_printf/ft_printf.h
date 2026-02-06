/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:19:50 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/20 13:06:23 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"

int		ft_printf(const char *format, ...);
int		ft_c(unsigned char c);
int		ft_s(const char *s);
int		ft_p(void *p);
int		ft_d_i(int d_i, int flags);
int		ft_u(unsigned int u);
int		ft_xx(const char **format, unsigned int xx, int flags);
int		ft_percent(void);

#endif
