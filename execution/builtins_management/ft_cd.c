/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:10:57 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/23 20:51:06 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	manage_hyphen(char *given_path, t_exec_resources *exec_resources,
	char **target_dir)
{
	if (given_path[1] != '\0')
	{
		ft_dprintf(2, "minishell: %s: invalid option\n", given_path);
		return (2);
	}
	*target_dir = get_local_env(exec_resources->local_envp, "OLDPWD");
	if (!target_dir)
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	*target_dir = ft_strdup(*target_dir);
	if (!*target_dir)
		return (3);
	printf("%s\n", *target_dir);
	return (0);
}

static int	determine_target_dir(char *given_path, char **target_dir,
	char *home, t_exec_resources *exec_resources)
{
	int	return_value;

	return_value = 0;
	if (given_path == NULL)
		*target_dir = ft_strdup(home);
	else if (given_path[0] == '-')
		return_value = manage_hyphen(given_path, exec_resources, target_dir);
	else if (given_path[0] == '~'
		&& (given_path[1] == '/' || given_path[1] == '\0'))
		*target_dir = ft_strjoin(home, given_path);
	else
		*target_dir = ft_strdup(given_path);
	if (!*target_dir)
	{
		ft_dprintf(2, "minishell: cd: malloc() failure\n");
		return_value = 4;
	}
	return (return_value);
}

static int	change_dir(char *target_dir, char *given_path)
{
	char	*err_str;

	if (chdir(target_dir) == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", given_path);
		free(target_dir);
		if (err_str != NULL)
		{
			perror(err_str);
			free(err_str);
		}
		return (1);
	}
	return (0);
}

static void	path_related_updates(char *target_dir,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	char		*old_internal_pwd;
	char		*final_path;

	final_path = define_non_reiterative_path(target_dir,
			exec_resources, prompt_resources->home);
	free(target_dir);
	old_internal_pwd = exec_resources->internal_pwd;
	exec_resources->internal_pwd = ft_strdup(final_path);
	update_local_env_paths(exec_resources, old_internal_pwd);
	free(old_internal_pwd);
	free(final_path);
	if (exec_resources->prompt != NULL)
		define_prompt(&exec_resources->prompt, prompt_resources,
			exec_resources->local_envp, exec_resources->internal_pwd);
	return ;
}

int	ft_cd(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	char		*target_dir;
	int			return_value;

	if (argv[1] != NULL && strncmp(argv[1], ".", 2) == 0)
		return (0);
	if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (2);
	}
	return_value = determine_target_dir(argv[1], &target_dir,
			prompt_resources->home, exec_resources);
	if (return_value != 0)
		return (return_value);
	if (change_dir(target_dir, argv[1]) == 0)
		path_related_updates(target_dir, exec_resources, prompt_resources);
	else
		return (1);
	return (0);
}
