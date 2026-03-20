/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:10:57 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 17:05:36 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	manage_hyphen(char **argv, t_exec_resources *exec_resources,
	char **final_path)
{
	if (argv[1][1] != '\0')
	{
		ft_dprintf(2, "minishell: %s: invalid option\n", argv[1]);
		return (2);
	}
	*final_path = get_local_env(exec_resources->local_envp, "OLDPWD");
	if (!final_path)
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	*final_path = ft_strdup(*final_path);
	if (!*final_path)
		return (3);
	printf("%s\n", *final_path);
	return (0);
}

static int	change_dir(char *final_path, char *given_path)
{
	char	*err_str;

	if (chdir(final_path) == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", given_path);
		free(final_path);
		if (err_str != NULL)
		{
			perror(err_str);
			free(err_str);
		}
		return (1);
	}
	return (0);
}

static void	path_related_updates(t_exec_resources *exec_resources,
	char *final_path, t_prompt_resources *prompt_resources)
{
	char		*old_internal_pwd;

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

static int	determine_final_path(char **argv, char **final_path,
	t_prompt_resources *prompt_resources, t_exec_resources *exec_resources)
{
	int	return_value;

	if (argv[1] == NULL)
		*final_path = ft_strdup(prompt_resources->home);
	else if (argv[1][0] == '-')
	{
		return_value = manage_hyphen(argv, exec_resources, final_path);
		if (return_value != 0)
			return (return_value);
	}
	else
		*final_path = define_non_reiterative_path(argv[1],
				exec_resources, prompt_resources->home);
	return (0);
}

int	ft_cd(char **argv, t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	char		*final_path;
	int			return_value;

	if (argv[1] != NULL && strncmp(argv[1], ".", 2) == 0)
		return (0);
	if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (2);
	}
	return_value = determine_final_path(argv, &final_path,
			prompt_resources, exec_resources);
	if (return_value > 0 && return_value < 3)
		return (return_value);
	if (final_path == NULL)
	{
		ft_dprintf(2, "minishell: cd: malloc() failure\n");
		return (3);
	}
	change_dir(final_path, argv[1]);
	path_related_updates(exec_resources, final_path, prompt_resources);
	return (0);
}
