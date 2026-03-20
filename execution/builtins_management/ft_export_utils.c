/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:39:04 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 19:47:16 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_identifier_check(char *requested_var)
{
	int	i;

	i = 0;
	if (ft_isdigit(requested_var[i]) || requested_var[i] == '=')
		return (1);
	while (requested_var[i] && requested_var[i] != '=')
	{
		if (!ft_isalnum(requested_var[i]) && requested_var[i] != '_'
			&& requested_var[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	replace_env_var(char *preexisting_env_var, char *var_name,
	char *requested_var)
{
	preexisting_env_var -= (ft_strlen(var_name) + 1);
	free(var_name);
	free(preexisting_env_var);
	preexisting_env_var = ft_strdup(requested_var);
	if (preexisting_env_var == NULL)
		return (2);
	return (0);
}

int	create_exports_list(t_new_exports **exports_node, char *requested_var)
{
	*exports_node = malloc(sizeof(t_new_exports));
	if (*exports_node == NULL)
		return (3);
	(*exports_node)->var = ft_strdup(requested_var);
	if ((*exports_node)->var == NULL)
		return (4);
	(*exports_node)->prev = NULL;
	(*exports_node)->next = NULL;
	return (0);
}

int	append_or_replace_exports_node(t_new_exports **new_exports,
	char *var_name, char *requested_var)
{
	t_new_exports	*curr_exp_var;
	t_new_exports	*preexisting_exp_var;

	curr_exp_var = *new_exports;
	preexisting_exp_var = get_local_exp(new_exports, var_name);
	free(var_name);
	if (preexisting_exp_var == NULL)
	{
		while (curr_exp_var->next != NULL)
			curr_exp_var = curr_exp_var->next;
		curr_exp_var->next = malloc(sizeof(t_new_exports));
		curr_exp_var->next->prev = curr_exp_var;
		curr_exp_var = curr_exp_var->next;
		if (curr_exp_var == NULL)
			return (5);
		curr_exp_var->var = ft_strdup(requested_var);
		if (curr_exp_var->var == NULL)
			return (6);
		curr_exp_var->next = NULL;
		return (0);
	}
	else
		return (replace_exp_var(preexisting_exp_var, requested_var));
}

int	replace_exp_var(t_new_exports *preexisting_exp_var,
	char *requested_var)
{
	free(preexisting_exp_var->var);
	preexisting_exp_var->var = ft_strdup(requested_var);
	if (preexisting_exp_var->var == NULL)
		return (7);
	return (0);
}
