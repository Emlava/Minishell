/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:24:14 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/28 18:20:05 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	determine_computer(char **hostname_or_computer,
	bool *free_hostname_or_computer, char **envp)
{	
	int		i;
	char	*tmp_str;

	i = 0;
	*hostname_or_computer = get_local_env(envp, "SESSION_MANAGER");
	if (*hostname_or_computer == NULL)
		return ;
	while (**hostname_or_computer && **hostname_or_computer != '/')
		(*hostname_or_computer)++;
	if (**hostname_or_computer == '\0')
		return ;
	(*hostname_or_computer)++;
	while ((*hostname_or_computer)[i] && (*hostname_or_computer)[i] != '.')
		i++;
	if ((*hostname_or_computer)[i] == '\0')
		return ;
	tmp_str = malloc(sizeof(char) * (i + 1)); // free
	if (tmp_str == NULL)
		return ;
	ft_strlcpy(tmp_str, *hostname_or_computer, i + 1);
	*hostname_or_computer = tmp_str;
	*free_hostname_or_computer = true;
	return ;
}

static void	define_permanent_prompt_substr(t_prompt_resources *prompt_resources, char **envp)
{
	char	*user;
	char	*hostname_or_computer;
	char	*tmp_str;
	bool	free_hostname_or_computer;

	user = get_local_env(envp, "USER");
	prompt_resources->permanent_prompt_substr = NULL;
	if (user != NULL)
	{
		free_hostname_or_computer = false;
		hostname_or_computer = get_local_env(envp, "HOSTNAME");
		if (hostname_or_computer == NULL)
			determine_computer(&hostname_or_computer, &free_hostname_or_computer, envp);
		if (hostname_or_computer == NULL)
			prompt_resources->permanent_prompt_substr = (ft_strjoin(user, "@42_minishell:")); // free
		else
		{
			user = ft_strjoin(user, "@"); // free
			if (free_hostname_or_computer == true)
			{
				tmp_str = hostname_or_computer;
				hostname_or_computer = ft_strjoin(tmp_str, ":"); // free
				free(tmp_str);
			}
			else
				hostname_or_computer = ft_strjoin(hostname_or_computer, ":"); // free
			prompt_resources->permanent_prompt_substr = ft_strjoin(user, hostname_or_computer); // free
			free(user);
			free(hostname_or_computer);
		}
	}
	if (prompt_resources->permanent_prompt_substr == NULL)
	{
		prompt_resources->permanent_prompt_substr = "42_minishell:";
		prompt_resources->free_permanent_substr = false;
	}
	else
		prompt_resources->free_permanent_substr = true;
	return ;
}

static void	get_working_dir(char **working_dir, char **envp, t_prompt_resources *prompt_resources)
{
	char	*tmp_str;

	*working_dir = get_local_env(envp, "PWD");
	if (*working_dir == NULL)
		return ;
	if (ft_strnstr(*working_dir, prompt_resources->home, prompt_resources->home_len) != NULL
		&& ((*working_dir)[prompt_resources->home_len] == '\0'
		|| (*working_dir)[prompt_resources->home_len] == '/'))
	{
		tmp_str = ft_strjoin("~", *working_dir + prompt_resources->home_len); // free
		*working_dir = ft_strjoin(tmp_str, "$ "); // free
		free(tmp_str);
	}
	else
		*working_dir = ft_strjoin(*working_dir, "$ "); // free
	return ;
}

void	define_prompt(char **prompt, t_prompt_resources *prompt_resources, char **envp)
{
	char	*working_dir;
	
	if (*prompt == NULL)
	{
		define_permanent_prompt_substr(prompt_resources, envp);
		prompt_resources->home = get_local_env(envp, "HOME");
		if (prompt_resources->home == NULL)
		{
			if (prompt_resources->free_permanent_substr == true)
				free(prompt_resources->permanent_prompt_substr);
			return ;
		}
		prompt_resources->home_len = ft_strlen(prompt_resources->home);
	}
	else
	{
		free(*prompt);
		*prompt = NULL;
	}
	get_working_dir(&working_dir, envp, prompt_resources);
	if (working_dir == NULL)
	{
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
		return ;
	}
	*prompt = ft_strjoin(prompt_resources->permanent_prompt_substr, working_dir); // free
	free(working_dir);
	return ;
}
