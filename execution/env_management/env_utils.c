/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:13:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/27 14:06:10 by elara-va         ###   ########.fr       */
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
	env_duplicate = malloc(sizeof(char*) * (env_var_count + 1)); // free
	if (env_duplicate == NULL)
		return (NULL);
	i = 0;
	while (i < env_var_count)
	{
		env_duplicate[i] = ft_strdup(envp[i]); // free each
		if (env_duplicate[i] == NULL)
		{
			free_str_arr(env_duplicate);
			return (NULL);
		}
		i++;
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
		exec_resources->last_command_present = false;
	else
		exec_resources->last_command_present = true;
	return ;
}

void	get_var_indexes(t_exec_resources *exec_resources)
{
	int	i;

	if (exec_resources->pwd_present == true)
	{
		i = 0;
		while (ft_strncmp(exec_resources->local_envp[i], "PWD=", 4))
			i++;
		exec_resources->pwd_index = i;
	}
	if (exec_resources->oldpwd_present == true)
	{
		i = 0;
		while (ft_strncmp(exec_resources->local_envp[i], "OLDPWD=", 7))
			i++;
		exec_resources->oldpwd_index = i;
	}
	if (exec_resources->last_command_present == true)
	{
		i = 0;
		while (ft_strncmp(exec_resources->local_envp[i], "_=", 2))
			i++;
		exec_resources->last_command_index = i;
	}
	return ;
}

char	*get_local_env(char **local_envp, char *name)
{
	char	*formatted_name;
	size_t	formatted_name_len;
	int		i;

	formatted_name = ft_strjoin(name, "="); // free
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

void	update_local_env_paths(t_exec_resources *exec_resources, char *new_pwd)
{
	if (exec_resources->oldpwd_present == true)
	{
		free(exec_resources->local_envp[exec_resources->oldpwd_index]);
		exec_resources->local_envp[exec_resources->oldpwd_index]
			= ft_strdup(exec_resources->local_envp[exec_resources->pwd_index]); // This is freed when freeing local_envp	
	}
	free(exec_resources->local_envp[exec_resources->pwd_index]);
	exec_resources->local_envp[exec_resources->pwd_index] = ft_strjoin("PWD=", new_pwd); // This is freed when freeing local_envp	
	return ;
}

void	update_local_env_last_command(t_exec_resources *exec_resources, char *last_command)
{
	free(exec_resources->local_envp[exec_resources->last_command_index]);
	exec_resources->local_envp[exec_resources->last_command_index] = ft_strjoin("_=", last_command); // This is freed when freeing local_envp	
	return ;
}
