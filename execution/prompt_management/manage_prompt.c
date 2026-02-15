/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/15 16:00:27 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	assign_local_resources(t_prompt *prompt_resources)
{
	prompt_resources->user = getenv("USER");
	if (prompt_resources->user == NULL)
		return (1);
	if (determine_second_field(prompt_resources) != 0)
		return (2);
	format_working_dir(prompt_resources);
	if (prompt_resources->working_dir == NULL)
	{
		if (prompt_resources->curr_computer_present == true)
			free(prompt_resources->host_or_computer);
		return (3);
	}
	return (0);
}

static int	format_prompt_substrings(t_prompt *prompt_resources)
{
	prompt_resources->user = ft_strjoin(prompt_resources->user, "@"); // free
	if (!prompt_resources->user)
		return (1);
	prompt_resources->host_or_computer
		= ft_strjoin(prompt_resources->host_or_computer, ":"); // free
	if (!prompt_resources->host_or_computer)
	{
		free_prompt_resources(prompt_resources, 1);
		return (2);
	}
	if (prompt_resources->tmp != NULL)
		free_and_null_tmp(prompt_resources);
	if (prompt_resources->working_dir[0] == '~')
		prompt_resources->tmp = prompt_resources->working_dir;
	prompt_resources->working_dir
		= ft_strjoin(prompt_resources->working_dir, "$ "); // free
	if (prompt_resources->tmp != NULL)
		free(prompt_resources->tmp);
	if (!prompt_resources->working_dir)
	{
		free_prompt_resources(prompt_resources, 2);
		return (3);
	}
	return (0);
}

static int	put_prompt_together(t_prompt *prompt_resources, char **prompt)
{
	if (format_prompt_substrings(prompt_resources) != 0)
		return (1);
	prompt_resources->tmp = ft_strjoin(prompt_resources->user,
			prompt_resources->host_or_computer); // free
	if (!prompt_resources->tmp)
	{
		free_prompt_resources(prompt_resources, 3);
		return (2);
	}
	*prompt = ft_strjoin(prompt_resources->tmp,
			prompt_resources->working_dir); // free
	free_prompt_resources(prompt_resources, 4);
	if (!(*prompt))
		return (3);
	return (0);
}

void	define_prompt(char **prompt)
{
	t_prompt	prompt_resources;

	if (assign_local_resources(&prompt_resources) != 0
		|| put_prompt_together(&prompt_resources, prompt) != 0)
		*prompt = "42_minishell: ";
	return ;
}
