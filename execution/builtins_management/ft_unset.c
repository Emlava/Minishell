/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:56:13 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 18:29:00 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	unset_inherited_var(char *env_var, char *requested_var)
{
	env_var -= ft_strlen(requested_var) + 1;
	env_var[0] = '\0';
	return ;
}

static void	unset_exported_var(t_new_exports *exp_var,
	t_exec_resources *exec_resources)
{
	free(exp_var->var);
	if (exp_var->prev != NULL)
		exp_var->prev->next = exp_var->next;
	else
		exec_resources->new_exports = exec_resources->new_exports->next;
	if (exp_var->next != NULL)
		exp_var->next->prev = exp_var->prev;
	free(exp_var);
	return ;
}

static void	find_and_unset_vars(char **argv, t_exec_resources *exec_resources)
{
	int				i;
	char			*env_var;
	t_new_exports	*exp_var;

	i = 1;
	while (argv[i] != NULL)
	{
		env_var = get_local_env(exec_resources->local_envp, argv[i]);
		if (env_var != NULL)
		{
			unset_inherited_var(env_var, argv[i]);
			i++;
			continue ;
		}
		exp_var = get_local_exp(&exec_resources->new_exports, argv[i]);
		if (exp_var != NULL)
			unset_exported_var(exp_var, exec_resources);
		i++;
	}
	if (env_var != NULL)
		get_var_indexes(exec_resources);
}

int	ft_unset(char **argv, t_exec_resources *exec_resources)
{
	if (argv[1] == NULL)
		return (0);
	if (argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: unset: %s: no options for this builtin\n",
			argv[1]);
		return (1);
	}
	find_and_unset_vars(argv, exec_resources);
	return (0);
}
