/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:49:38 by elara-va          #+#    #+#             */
/*   Updated: 2025/05/10 17:26:00 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}

/*int	main(void)
{
	char *s = "Hello!";
	int fd = 1;

	ft_putendl_fd(s, fd);
	return (0);
}*/
