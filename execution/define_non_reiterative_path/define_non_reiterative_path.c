/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_non_reiterative_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:18:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 17:29:58 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*manage_relative_path(char *requested_path, char *pwd)
{
	char	*absolute_path;
	char	*tmp_str;
	char	*final_path;

	tmp_str = ft_strjoin(pwd, "/");
	absolute_path = ft_strjoin(tmp_str, requested_path);
	free(tmp_str);
	final_path = manage_absolute_path(absolute_path);
	free(absolute_path);
	return (final_path);
}

static void	manage_tilde(char **requested_path, char *home)
{
	*requested_path = ft_strjoin(home, (*requested_path) + 1);
	return ;
}

char	*define_non_reiterative_path(char *requested_path,
	t_exec_resources *exec_resources, char *home)
{
	char	*final_path;

	if (ft_strncmp(requested_path, "/", 2) == 0)
		return (ft_strdup(requested_path));
	if (requested_path[0] == '~'
		&& (requested_path[1] == '/' || requested_path[1] == '\0'))
	{
		manage_tilde(&requested_path, home);
		if (requested_path == NULL)
			return (NULL);
	}
	if (requested_path[0] == '/')
		final_path = manage_absolute_path(requested_path);
	else
		final_path = manage_relative_path(requested_path,
				exec_resources->internal_pwd);
	return (final_path);
}
