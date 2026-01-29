/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:35 by elara-va          #+#    #+#             */
/*   Updated: 2026/01/29 15:34:38 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	*usr_command;

	prompt = "42_minishell: ";
	usr_command = readline(prompt);
	printf("The command entered by the user was: %s\n", usr_command);
	free(usr_command);
	return (0);
}
