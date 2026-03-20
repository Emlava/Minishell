/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:33:02 by hudescam          #+#    #+#             */
/*   Updated: 2026/03/20 19:40:52 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_permanent_prompt(t_prompt_resources *prompt_resources)
{
	if (prompt_resources->permanent_prompt_substr == NULL)
	{
		prompt_resources->permanent_prompt_substr = "42_minishell:";
		prompt_resources->free_permanent_substr = false;
	}
	else
		prompt_resources->free_permanent_substr = true;
}

void	construct_permanent_prompt(t_prompt_resources *prompt_resources,
	char *user, char *hostname_or_computer, bool free_hostname_or_computer)
{
	char	*tmp_str;

	user = ft_strjoin(user, "@");
	if (free_hostname_or_computer == true)
	{
		tmp_str = hostname_or_computer;
		hostname_or_computer = ft_strjoin(tmp_str, ":");
		free(tmp_str);
	}
	else
		hostname_or_computer = ft_strjoin(hostname_or_computer, ":");
	prompt_resources->permanent_prompt_substr = ft_strjoin(
			user, hostname_or_computer);
	free(user);
	free(hostname_or_computer);
}

bool	setup_prompt_home(char **prompt, t_prompt_resources *prompt_resources,
	char **envp)
{
	(void)prompt;
	prompt_resources->home = get_local_env(envp, "HOME");
	if (prompt_resources->home == NULL)
	{
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
		return (false);
	}
	prompt_resources->home_len = ft_strlen(prompt_resources->home);
	return (true);
}
