/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/08 17:34:07 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*format_working_dir(void)
{
	char	*working_dir;
	char	*tmp;
	int		i;

	working_dir = getcwd(NULL, 0); // free
	if (working_dir != NULL && ft_strncmp(working_dir, "/home/", 6) == 0)
	{
		tmp = working_dir;
		i = 6;
		while (working_dir[i] && working_dir[i] != '/')
			i++;
		working_dir = ft_strjoin("~", working_dir + i); // free
		free(tmp);
	}
	return (working_dir);
}

static void	free_local_resources(char *user, char *host_name,
	char *working_dir, char *tmp)
{
	free(user);
	free(host_name);
	free(working_dir);
	free(tmp);
	return ;
}

void	define_prompt(char **prompt)
{
	char	*user;
	char	*host_name;
	char	*working_dir;
	char	*tmp;

	user = getenv("USER");
	working_dir = format_working_dir();
	host_name = getenv("HOSTNAME");
	tmp = NULL;
	if (user == NULL || host_name == NULL || working_dir == NULL)
		*prompt = "42_minishell: ";
	else
	{
		user = ft_strjoin(user, "@"); // free
		host_name = ft_strjoin(host_name, ":"); // free
		if (working_dir[0] == '~')
			tmp = working_dir;
		working_dir = ft_strjoin(working_dir, "$ "); // free
		if (tmp != NULL)
			free(tmp);
		tmp = ft_strjoin(user, host_name); // free
		*prompt = ft_strjoin(tmp, working_dir); // free
		free_local_resources(user, host_name, working_dir, tmp);
	}
	return ;
}
