/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:43:04 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 17:50:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_variables(t_exec_resources *exec_resources)
{
	int				i;
	t_new_exports	*curr_exp_var;

	i = 0;
	while (exec_resources->local_envp[i] != NULL)
	{
		if ((exec_resources->last_arg_present == false
				|| i != exec_resources->last_arg_index)
			&& exec_resources->local_envp[i][0])
			printf("%s\n", exec_resources->local_envp[i]);
		i++;
	}
	curr_exp_var = exec_resources->new_exports;
	while (curr_exp_var != NULL)
	{
		printf("%s\n", curr_exp_var->var);
		curr_exp_var = curr_exp_var->next;
	}
	if (exec_resources->last_arg_present == true)
		printf("%s\n",
			exec_resources->local_envp[exec_resources->last_arg_index]);
}

int	ft_env(char **argv, t_exec_resources *exec_resources)
{
	if (argv[1] != NULL)
	{
		ft_dprintf(2, "minishell: env: no options for this builtin\n");
		return (1);
	}
	print_variables(exec_resources);
	return (0);
}
