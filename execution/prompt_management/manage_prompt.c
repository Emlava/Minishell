/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 16:24:14 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 19:38:02 by hudescam         ###   ########.fr       */
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
	tmp_str = malloc(sizeof(char) * (i + 1));
	if (tmp_str == NULL)
		return ;
	ft_strlcpy(tmp_str, *hostname_or_computer, i + 1);
	*hostname_or_computer = tmp_str;
	*free_hostname_or_computer = true;
}

static void	define_permanent_prompt_substr(t_prompt_resources *prompt_resources,
	char **envp)
{
	char	*user;
	char	*hostname_or_computer;
	bool	free_hostname_or_computer;

	user = get_local_env(envp, "USER");
	prompt_resources->permanent_prompt_substr = NULL;
	if (user != NULL)
	{
		free_hostname_or_computer = false;
		hostname_or_computer = get_local_env(envp, "HOSTNAME");
		if (hostname_or_computer == NULL)
			determine_computer(&hostname_or_computer,
				&free_hostname_or_computer, envp);
		if (hostname_or_computer == NULL)
			prompt_resources->permanent_prompt_substr = ft_strjoin(
					user, "@42_minishell:");
		else
			construct_permanent_prompt(prompt_resources, user,
				hostname_or_computer, free_hostname_or_computer);
	}
	check_permanent_prompt(prompt_resources);
}

static void	get_working_dir(char **working_dir,
	t_prompt_resources *prompt_resources)
{
	char	*tmp_str;

	if (*working_dir == NULL)
		return ;
	if (ft_strnstr(*working_dir, prompt_resources->home,
			prompt_resources->home_len) != NULL
		&& ((*working_dir)[prompt_resources->home_len] == '\0'
		|| (*working_dir)[prompt_resources->home_len] == '/'))
	{
		tmp_str = ft_strjoin("~", *working_dir + prompt_resources->home_len);
		*working_dir = ft_strjoin(tmp_str, "$ ");
		free(tmp_str);
	}
	else
		*working_dir = ft_strjoin(*working_dir, "$ ");
}

void	define_prompt(char **prompt, t_prompt_resources *prompt_resources,
	char **envp, char *internal_pwd)
{
	char	*working_dir;

	if (*prompt == NULL)
	{
		define_permanent_prompt_substr(prompt_resources, envp);
		if (!setup_prompt_home(prompt, prompt_resources, envp))
			return ;
	}
	else
	{
		free(*prompt);
		*prompt = NULL;
	}
	working_dir = internal_pwd;
	get_working_dir(&working_dir, prompt_resources);
	if (working_dir == NULL)
	{
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
		return ;
	}
	*prompt = ft_strjoin(prompt_resources->permanent_prompt_substr,
			working_dir);
	free(working_dir);
}
