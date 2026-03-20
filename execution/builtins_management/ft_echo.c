/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:05:26 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 16:10:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_valid_n_option(char **option_strs, int *i)
{
	int		j;
	bool	return_value;

	return_value = false;
	while (option_strs[*i])
	{
		j = 0;
		if (option_strs[*i][j++] == '-')
		{
			while (option_strs[*i][j] == 'n')
				j++;
			if (option_strs[*i][j] == '\0')
			{
				(*i)++;
				if (return_value == false)
					return_value = true;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (return_value);
}

int	ft_echo(char **argv)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = is_valid_n_option(argv, &i);
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
	return (0);
}
