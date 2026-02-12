/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/12 15:35:08 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	format_working_dir(t_prompt *prompt_resources)
{
	char	*local_tmp;
	int		i;

	if (prompt_resources->hostname_present == true)
		prompt_resources->working_dir = getcwd(NULL, 0); // free
	else
		prompt_resources->working_dir = getenv("PWD");
	if (prompt_resources->working_dir != NULL
		&& ft_strncmp(prompt_resources->working_dir, "/home/", 6) == 0)
	{
		local_tmp = prompt_resources->working_dir;
		i = 6;
		while (prompt_resources->working_dir[i]
			&& prompt_resources->working_dir[i] != '/')
			i++;
		prompt_resources->working_dir = ft_strjoin("~",
				prompt_resources->working_dir + i); // free
		if (prompt_resources->hostname_present == true)
			free(local_tmp);
	}
}

static int	assign_local_resources(t_prompt *prompt_resources)
{
	int	i;

	i = 0;
	prompt_resources->user = getenv("USER");
	if (prompt_resources->user == NULL)
		return (1);
	prompt_resources->host_or_computer = getenv("HOSTNAME");
	if (prompt_resources->host_or_computer == NULL)
	{
		prompt_resources->hostname_present = false;
		prompt_resources->host_or_computer = getenv("SESSION_MANAGER");
		if (prompt_resources->host_or_computer != NULL
			&& ft_strncmp(prompt_resources->host_or_computer, "local/", 6) == 0)
		{
			i = 5;
			while ((prompt_resources->host_or_computer)[i + 1] != '.'
			&& (prompt_resources->host_or_computer)[i + 1] != '\0')
				i++;
			prompt_resources->tmp = malloc(sizeof(char) * (i - 4));
			if (!prompt_resources->tmp)
				return (2);
			prompt_resources->host_or_computer
				= ft_memcpy(prompt_resources->tmp,
					prompt_resources->host_or_computer + 6, i - 5); // free
			(prompt_resources->host_or_computer)[i - 5] = '\0';
			if (ft_strncmp(prompt_resources->host_or_computer, "shi-", 4)
				&& ft_strncmp(prompt_resources->host_or_computer, "fu-", 3)
				&& ft_strncmp(prompt_resources->host_or_computer,
					"mi-", 3))
			{
				free (prompt_resources->host_or_computer);
				return (3);
			}
		}
		else
			return (4);
	}
	else
	{
		prompt_resources->hostname_present = true;
		prompt_resources->tmp = NULL;
	}
	format_working_dir(prompt_resources);
	if (prompt_resources->working_dir == NULL)
	{
		if (i != 0)
			free(prompt_resources->host_or_computer);
		return (5);
	}
	return (0);
}

static void	free_prompt_resources(t_prompt *prompt_resources)
{
	free(prompt_resources->user);
	free(prompt_resources->host_or_computer);
	free(prompt_resources->working_dir);
	free(prompt_resources->tmp);
	return ;
}

void	define_prompt(char **prompt)
{
	t_prompt	prompt_resources;

	if (assign_local_resources(&prompt_resources) != 0)
		*prompt = "42_minishell: ";
	else
	{
		prompt_resources.user = ft_strjoin(prompt_resources.user, "@"); // free
		prompt_resources.host_or_computer
			= ft_strjoin(prompt_resources.host_or_computer, ":"); // free
		if (prompt_resources.tmp != NULL)
		{
			free(prompt_resources.tmp);
			prompt_resources.tmp = NULL;
		}
		if (prompt_resources.working_dir[0] == '~')
			prompt_resources.tmp = prompt_resources.working_dir;
		prompt_resources.working_dir
			= ft_strjoin(prompt_resources.working_dir, "$ "); // free
		if (prompt_resources.tmp != NULL)
			free(prompt_resources.tmp);
		prompt_resources.tmp = ft_strjoin(prompt_resources.user,
				prompt_resources.host_or_computer); // free
		*prompt = ft_strjoin(prompt_resources.tmp,
				prompt_resources.working_dir); // free
		free_prompt_resources(&prompt_resources);
	}
	return ;
}
