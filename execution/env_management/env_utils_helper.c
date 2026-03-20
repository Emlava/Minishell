/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:17:14 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 19:02:55 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
