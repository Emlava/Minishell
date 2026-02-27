/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:18:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/27 18:06:59 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_next_dir(char **fields, int fields_count, int *curr_field)
{
	while (*curr_field < fields_count)
	{
		if (fields[*curr_field] != NULL)
			return (fields[*curr_field]);
		(*curr_field)++;
	}
	return (NULL);
}

static char *put_final_path_together(char **fields, int fields_count)
{
	char	*path;
	int		curr_field;
	bool	first_instance;
	char	*next_dir;
	char	*tmp_str;
	
	path = ft_strdup("/"); // free
	curr_field = 0;
	first_instance = true;
	while (curr_field < fields_count)
	{
		next_dir = find_next_dir(fields, fields_count, &curr_field);
		if (next_dir != NULL)
		{
			if (first_instance == true)
				first_instance = false;
			else
				next_dir = ft_strjoin("/", next_dir); // free
			tmp_str = path;
			path = ft_strjoin(path, next_dir); // free
			free(tmp_str);
		}
		if (first_instance == false)
			free(next_dir);
	}
	return (path);
}

static void	manage_absolute_path(char **argv, char **fields)
{
	int			fields_count;
	int			curr_field;
	int			i;

	free(argv[1]);
	fields_count = 0;
	while (fields[fields_count] != NULL)
	{
		if (ft_strncmp(fields[fields_count], ".", 2) == 0)
		{
			free(fields[fields_count]);
			fields[fields_count] = NULL;
		}
		fields_count++;
	}
	curr_field = 0;
	
	while (curr_field < fields_count)
	{
		if (ft_strncmp(fields[curr_field], "..", 3) == 0)
		{
			free(fields[fields_count]);
			fields[fields_count] = NULL;
			i = curr_field - 1;
			while (i > 0 && fields[i] == NULL)
				i--;
			if (i >= 0 && fields[i] != NULL)
			{
				free(fields[fields_count]);
				fields[fields_count] = NULL;
			}
		}
		curr_field++;
	}

	curr_field = 0;
	argv[1] = put_final_path_together(fields, fields_count);
	return ;
}

static char	**manage_realtive_path(char **argv, char *pwd, char **fields)
{
	int		fields_count;
	char	*tmp_str;

	free(argv[1]);
	fields_count = 0;
	while (fields[fields_count] != NULL)
		fields_count++;
}

void	define_non_reiterative_path(char **argv, t_exec_resources *exec_resources,
	char *home)
{
	char	**fields;
	char	*pwd;

	if (argv[1] == NULL)
	{
		argv[1] = ft_strdup(home); // Should be freed by free_cmds()
		return ;
	}
	if (ft_strncmp(argv[1], "/", 2) == 0)
		return ;
	fields = ft_split(argv[1], '/'); // free with special method in manage_*_path()
	if (fields == NULL)
	{
		free(argv[1]);
		argv[1] == NULL;
		return ;
	}
	if (ft_strncmp(fields[0], "~", 2) == 0)
	{
		free(fields[0]);
		fields[0] = ft_strdup(home); // free
		if (fields[0] == NULL)
		{
			free(argv[1]);
			argv[1] == NULL;
			return ;
		}
	}
	if (argv[1][0] == '/')
		manage_absolute_path(argv, fields);
	else
	{
		if (exec_resources->pwd_present == true)
			pwd = exec_resources->local_envp[exec_resources->pwd_index];
		else
			pwd = NULL;
		manage_realtive_path(argv, pwd, fields);
	}
	return ;
}

void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	free(exec_resources->user_input);
	free_cmds(exec_resources->command_list);
	free_str_arr(exec_resources->local_envp);
	if (exec_resources->prompt != NULL)
	{
		free(exec_resources->prompt);
		if (prompt_resources->free_permanent_substr == true)
			free(prompt_resources->permanent_prompt_substr);
	}
	rl_clear_history();
	// if piping or redirections: close fds
	return ;
}
