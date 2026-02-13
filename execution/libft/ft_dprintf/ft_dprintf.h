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

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H
# include "../libft.h"

int		ft_dprintf(int fd, const char *format, ...);
int		ft_d_c(int fd, unsigned char c);
int		ft_d_s(int fd, const char *s);
int		ft_d_p(int fd, void *p);
int		ft_d_di(int fd, int d_i, int flags);
int		ft_d_u(int fd, unsigned int u);
int		ft_d_xx(int fd, const char **format, unsigned int xx, int flags);
int		ft_d_percent(int fd);

#endif
