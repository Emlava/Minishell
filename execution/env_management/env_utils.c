/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:13:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 19:05:59 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**duplicate_environment(char *envp[])
{
	int		env_var_count;
	int		i;
	char	**env_duplicate;

	env_var_count = 0;
	while (envp[env_var_count] != NULL)
		env_var_count++;
	env_duplicate = malloc(sizeof(char *) * (env_var_count + 1));
	if (env_duplicate == NULL)
		return (NULL);
	i = -1;
	while (++i < env_var_count)
	{
		if (ft_strncmp(envp[i], "_=", 2) != 0)
			env_duplicate[i] = ft_strdup(envp[i]);
		else
			env_duplicate[i] = ft_strdup("_=./minishell");
		if (env_duplicate[i] == NULL)
		{
			ft_free_str_arr(env_duplicate);
			return (NULL);
		}
	}
	env_duplicate[i] = NULL;
	return (env_duplicate);
}

void	check_essential_env_vars(t_exec_resources *exec_resources)
{
	if (get_local_env(exec_resources->local_envp, "PWD") == NULL)
		exec_resources->pwd_present = false;
	else
		exec_resources->pwd_present = true;
	if (get_local_env(exec_resources->local_envp, "OLDPWD") == NULL)
		exec_resources->oldpwd_present = false;
	else
		exec_resources->oldpwd_present = true;
	if (get_local_env(exec_resources->local_envp, "_") == NULL)
		exec_resources->last_arg_present = false;
	else
		exec_resources->last_arg_present = true;
	return ;
}

void	get_var_indexes(t_exec_resources *exec_resources)
{
	int	i;

	i = 0;
	get_var_indexes_helper(exec_resources);
	while (exec_resources->local_envp[i]
		&& ft_strncmp(exec_resources->local_envp[i], "_=", 2))
		i++;
	if (exec_resources->local_envp[i])
	{
		exec_resources->last_arg_index = i;
		exec_resources->last_arg_present = true;
	}
	else
		exec_resources->last_arg_present = false;
	return ;
}

char	*get_local_env(char **local_envp, char *name)
{
	char	*formatted_name;
	size_t	formatted_name_len;
	int		i;

	formatted_name = ft_strjoin(name, "=");
	if (formatted_name == NULL)
		return (NULL);
	formatted_name_len = ft_strlen(formatted_name);
	i = 0;
	while (local_envp[i] != NULL
		&& ft_strncmp(local_envp[i], formatted_name, formatted_name_len))
		i++;
	free(formatted_name);
	if (local_envp[i] == NULL)
		return (NULL);
	return (local_envp[i] + formatted_name_len);
}

t_new_exports	*get_local_exp(t_new_exports **new_exports, char *name)
{
	char			*formatted_name;
	size_t			formatted_name_len;
	t_new_exports	*curr_exp_var;

	if (*new_exports == NULL)
		return (NULL);
	formatted_name = ft_strjoin(name, "=");
	if (formatted_name == NULL)
		return (NULL);
	formatted_name_len = ft_strlen(formatted_name);
	curr_exp_var = *new_exports;
	while (curr_exp_var != NULL
		&& ft_strncmp(curr_exp_var->var, formatted_name, formatted_name_len))
		curr_exp_var = curr_exp_var->next;
	free(formatted_name);
	if (curr_exp_var == NULL)
		return (NULL);
	return (curr_exp_var);
}
