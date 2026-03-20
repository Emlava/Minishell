/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:41:51 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 17:42:35 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	int	exit_status;

	printf("exit\n");
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		if (!ft_is_numeric_str(argv[1]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric arguments required\n",
				argv[1]);
			exit_status = 2;
		}
		else
			exit_status = ft_atoi(argv[1]);
	}
	else
		exit_status = exec_resources->curr_exit_status;
	exit_cleanup(exec_resources, prompt_resources);
	exit(exit_status);
}
