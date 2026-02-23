/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/23 19:19:00 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	assign_local_resources(t_prompt *prompt_resources, bool *hostname_present)
{
	prompt_resources->user = get_local_env(prompt_resources->envp, "USER");
	if (prompt_resources->user == NULL)
		return (1);
	if (determine_second_field(prompt_resources, hostname_present) != 0)
		return (2);
	format_working_dir(prompt_resources, *hostname_present);
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

static int	put_prompt_together(t_prompt *prompt_resources, char **prompt, size_t *permanent_fields_len)
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
	while ((*prompt)[*permanent_fields_len] != ':')
		(*permanent_fields_len)++;
	(*permanent_fields_len)++;
	return (0);
}

void	define_prompt(char **prompt, char **local_envp)
{
	t_prompt		prompt_resources;
	static size_t	permanent_fields_len;
	static bool		hostname_present;
	char			*permanent_fields_str;

	prompt_resources.envp = local_envp;
	if (*prompt == NULL)
	{
		if (assign_local_resources(&prompt_resources, &hostname_present) != 0
			|| put_prompt_together(&prompt_resources, prompt, &permanent_fields_len) != 0)
		{
			format_working_dir(&prompt_resources, hostname_present);
			prompt_resources.tmp = ft_strjoin("42_minishell:", prompt_resources.working_dir);
			if (prompt_resources.working_dir[0] == '~')
				free(prompt_resources.working_dir);
			*prompt = ft_strjoin(prompt_resources.tmp, "$ ");
			free(prompt_resources.tmp);
		}
	}
	else
	{
		permanent_fields_str = malloc(sizeof(char) * (permanent_fields_len + 1)); // free
		ft_strlcpy(permanent_fields_str, *prompt, permanent_fields_len);
		free(*prompt);
		format_working_dir(&prompt_resources, hostname_present);
		prompt_resources.tmp = ft_strjoin(permanent_fields_str, prompt_resources.working_dir);
		if (prompt_resources.working_dir[0] == '~')
			free(prompt_resources.working_dir);
		*prompt = ft_strjoin(prompt_resources.tmp, "$ ");
	}
	return ;
}

// Resources to free:
// -user (in some cases) in define_prompt(), freed
// -host_or_computer (in some cases) in define_prompt(), freed
// -working_dir (in some cases) in define_prompt() and
// format_working_dir, both freed
// -tmp (in some cases {two possible instances}) in define_prompt(), freed
// -prompt (if it's not NULL), freed
