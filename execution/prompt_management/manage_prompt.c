/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/21 17:26:45 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Check where to place this function and add to execution.h
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

// Resources to free:
// -user (in some cases) in define_prompt(), freed
// -host_or_computer (in some cases) in define_prompt(), freed
// -working_dir (in some cases) in define_prompt() and
// format_working_dir, both freed
// -tmp (in some cases {two possible instances}) in define_prompt(), freed
// -prompt (if it's not "42_minishell: "), freed
