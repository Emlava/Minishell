/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:38:09 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/14 19:29:37 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	determine_computer(t_prompt *prompt_resources)
{
	int	i;

	prompt_resources->host_or_computer = getenv("SESSION_MANAGER");
	if (prompt_resources->host_or_computer != NULL
		&& ft_strncmp(prompt_resources->host_or_computer, "local/", 6) == 0)
	{
		prompt_resources->curr_computer_present = true;
		i = 5;
		while ((prompt_resources->host_or_computer)[i + 1] != '.'
		&& (prompt_resources->host_or_computer)[i + 1] != '\0')
			i++;
		prompt_resources->tmp = malloc(sizeof(char) * (i - 4));
		if (!prompt_resources->tmp)
			return (1);
		prompt_resources->host_or_computer = ft_memcpy(prompt_resources->tmp,
				prompt_resources->host_or_computer + 6, i - 5); // free
		(prompt_resources->host_or_computer)[i - 5] = '\0';
	}
	else
	{
		prompt_resources->curr_computer_present = false;
		return (2);
	}
	return (0);
}

int	determine_second_field(t_prompt *prompt_resources)
{
	int	determine_computer_return_value;

	prompt_resources->host_or_computer = getenv("HOSTNAME");
	if (prompt_resources->host_or_computer == NULL)
	{
		prompt_resources->hostname_present = false;
		determine_computer_return_value = determine_computer(prompt_resources);
		if (determine_computer_return_value == 1)
			return (1);
		if (determine_computer_return_value == 2)
			prompt_resources->host_or_computer = "42_minishell";
	}
	else
	{
		prompt_resources->hostname_present = true;
		prompt_resources->tmp = NULL;
	}
	return (0);
}

void	format_working_dir(t_prompt *prompt_resources)
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
	return ;
}

void	free_and_null_tmp(t_prompt *prompt_resources)
{
	free(prompt_resources->tmp);
	prompt_resources->tmp = NULL;
	return ;
}

// Instance 1: free user.
// Instance 2: free user and host_or_computer.
// Instance 3: free user, host_or_computer and working_dir.
// Instance 4: free user, host_or_computer, working_dir and tmp.
void	free_prompt_resources(t_prompt *prompt_resources, int instance)
{
	free(prompt_resources->user);
	if (instance > 1)
	{
		free(prompt_resources->host_or_computer);
		if (instance > 2)
		{
			free(prompt_resources->working_dir);
			if (instance == 4)
				free(prompt_resources->tmp);
		}
	}
	return ;
}
