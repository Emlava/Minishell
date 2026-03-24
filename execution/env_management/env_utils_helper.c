/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:17:14 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/24 19:48:16 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	replace_env_var(char **envp, int var_index, char *requested_var)
{
	free(envp[var_index]);
	envp[var_index] = ft_strdup(requested_var);
	if (envp[var_index] == NULL)
		return (1);
	return (0);
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

void	get_var_indexes_helper(t_exec_resources *exec_resources)
{
	int	i;

	i = 0;
	while (exec_resources->local_envp[i]
		&&ft_strncmp(exec_resources->local_envp[i], "PWD=", 4))
		i++;
	if (exec_resources->local_envp[i])
	{
		exec_resources->pwd_index = i;
		exec_resources->pwd_present = true;
	}
	else
		exec_resources->pwd_present = false;
	i = 0;
	while (exec_resources->local_envp[i]
		&& ft_strncmp(exec_resources->local_envp[i], "OLDPWD=", 7))
		i++;
	if (exec_resources->local_envp[i])
	{
		exec_resources->oldpwd_index = i;
		exec_resources->oldpwd_present = true;
	}
	else
		exec_resources->oldpwd_present = false;
}

void	update_local_env_paths(t_exec_resources *res, char *old_pwd)
{
	if (res->pwd_present == true)
	{
		free(res->local_envp[res->pwd_index]);
		res->local_envp[res->pwd_index]
			= ft_strjoin("PWD=", res->internal_pwd);
	}
	if (res->oldpwd_present == true)
	{
		free(res->local_envp[res->oldpwd_index]);
		res->local_envp[res->oldpwd_index]
			= ft_strjoin("OLDPWD=", old_pwd);
	}
}

void	update_local_env_last_arg(t_exec_resources *exec_resources, char **argv)
{
	char	*last_arg;
	int		i;

	i = 0;
	while (argv[i + 1] != NULL)
		i++;
	last_arg = argv[i];
	free(exec_resources->local_envp[exec_resources->last_arg_index]);
	exec_resources->local_envp[exec_resources->last_arg_index]
		= ft_strjoin("_=", last_arg);
}
