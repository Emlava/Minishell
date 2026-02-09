/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/09 21:04:30 by elara-va         ###   ########.fr       */
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

static int	assign_local_resources(char **user, char **host_or_computer,
	char **working_dir, char **tmp)
{
	int	i;

	*user = getenv("USER");
	if (*user == NULL)
		return (1);
	*host_or_computer = getenv("HOSTNAME");
	if (*host_or_computer == NULL)
	{
		*host_or_computer = getenv("SESSION_MANAGER");
		if (*host_or_computer != NULL && ft_strncmp(*host_or_computer, "local/", 6) == 0)
		{
			i = 6;
			while (*host_or_computer[i + 1] != '.' || *host_or_computer[i + 1] != '\0')
				i++;
			*tmp = malloc(sizeof(char) * (i - 4));
			*host_or_computer = ft_memcpy(*tmp, *host_or_computer + 6, i - 5); // free
			*host_or_computer[i - 6] = '\0';
			if (ft_strncmp(*host_or_computer, "shi-", 4) || ft_strncmp(*host_or_computer, "fu-", 3
				|| ft_strncmp(*host_or_computer, "mi-", 3)))
			{
				free (*host_or_computer);
				return (2);
			}
		}
		else
			return (3);
	}
	*working_dir = format_working_dir();
	if (*working_dir == NULL)
	{
		free(*host_or_computer);
		return (4);
	}
	return (0);
}

static void	free_local_resources(char *user, char *host_or_computer,
	char *working_dir, char *tmp)
{
	free(user);
	free(host_or_computer);
	free(working_dir);
	free(tmp);
	return ;
}

void	define_prompt(char **prompt)
{
	char	*user;
	char	*host_or_computer;
	char	*working_dir;
	char	*tmp;

	if (assign_local_resources(&user, &host_or_computer, &working_dir, &tmp) != 0)
		*prompt = "42_minishell: ";
	else
	{
		user = ft_strjoin(user, "@"); // free
		host_or_computer = ft_strjoin(host_or_computer, ":"); // free
		free(tmp);
		tmp = NULL;
		if (working_dir[0] == '~')
			tmp = working_dir;
		working_dir = ft_strjoin(working_dir, "$ "); // free
		if (tmp != NULL)
			free(tmp);
		tmp = ft_strjoin(user, host_or_computer); // free
		*prompt = ft_strjoin(tmp, working_dir); // free
		free_local_resources(user, host_or_computer, working_dir, tmp);
	}
	return ;
}
