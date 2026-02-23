/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_manage_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:24:14 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/23 21:15:31 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	define_permanent_prompt_substr(t_prompt_resources *prompt_resources, char **envp)
{
	char	*user;
	char	*hostname_or_computer;

	user = get_local_env(envp, "USER");
	prompt_resources->permanent_prompt_substr = NULL;
	if (user != NULL)
	{
		hostname_or_computer = get_local_env(envp, "HOSTNAME");
		if (hostname_or_computer == NULL)
			hostname_or_computer = get_local_env(envp, "SESSION_MANAGER");
		if (hostname_or_computer == NULL)
			prompt_resources->permanent_prompt_substr = (ft_strjoin(user, "@42_minishell:")); // free
		else
		{
			user = ft_strjoin(user, "@"); // free
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

void	get_working_dir(char **working_dir, char **envp, t_prompt_resources *prompt_resources)
{
	char	*tmp_str;

	*working_dir = get_local_env(envp, "PWD");
	if (*working_dir == NULL)
		return ;
	if (ft_strnstr(*working_dir, prompt_resources->home, prompt_resources->home_len) != NULL)
	{
		tmp_str = ft_strjoin("~", *working_dir + prompt_resources->home_len); // free
		*working_dir = ft_strjoin(tmp_str, "$ "); // free
		free(tmp_str);
	}
	else
		*working_dir = ft_strjoin(*working_dir, "$ "); // free
	return ;
}

void	n_define_prompt(char **prompt, t_prompt_resources *prompt_resources, char **envp)
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
	get_working_dir(&working_dir, envp, prompt_resources);
	if (get_working_dir == NULL)
	{
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
		return ;
	}
	*prompt = ft_strjoin(prompt_resources->permanent_prompt_substr, working_dir); // free
	free(working_dir);
	return ;
}
