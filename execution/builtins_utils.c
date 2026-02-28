/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:18:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/28 17:44:38 by elara-va         ###   ########.fr       */
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
	bool	first_iteration;
	char	*next_dir;
	char	*tmp_str;
	
	path = ft_strdup("/"); // free
	curr_field = 0;
	first_iteration = true;
	while (curr_field < fields_count)
	{
		next_dir = find_next_dir(fields, fields_count, &curr_field);
		if (next_dir != NULL)
		{
			if (first_iteration == false)
				next_dir = ft_strjoin("/", next_dir); // free
			tmp_str = path;
			path = ft_strjoin(path, next_dir); // free
			free(tmp_str);
			if (first_iteration == true)
				first_iteration = false;
			else
				free(next_dir);
		}
		curr_field++;
	}
	return (path);
}

static void	free_fields(char **fields, int fields_count)
{
	while (--fields_count >= 0)
	{
		if (fields[fields_count] != NULL)
			free(fields[fields_count]);
	}
	free(fields);
}

static char	*manage_absolute_path(char *requested_path)
{
	char		**fields;
	int			fields_count;
	int			curr_field;
	int			i;
	char		*final_path;

	fields = ft_split(requested_path, '/'); // free with special method in free_fields()
	if (fields == NULL)
		return (NULL);
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
		if (fields[curr_field] != NULL && ft_strncmp(fields[curr_field], "..", 3) == 0)
		{
			free(fields[curr_field]);
			fields[curr_field] = NULL;
			i = curr_field - 1;
			while (i > 0 && fields[i] == NULL)
				i--;
			if (i >= 0 && fields[i] != NULL)
			{
				free(fields[i]);
				fields[i] = NULL;
			}
		}
		curr_field++;
	}
	final_path = put_final_path_together(fields, fields_count);
	free_fields(fields, fields_count);
	return (final_path);
}

static char	*manage_relative_path(char *requested_path, char *pwd)
{
	char	*absolute_path;
	char	*tmp_str;
	char	*final_path;

	tmp_str = ft_strjoin(pwd + 4, "/");
	absolute_path = ft_strjoin(tmp_str, requested_path);
	free(tmp_str);
	final_path = manage_absolute_path(absolute_path);
	free(absolute_path);
	return (final_path);
}

static void	manage_tilde(char **argv, char *home)
{
	char	*tmp_str;
	
	tmp_str = argv[1];
	argv[1] = ft_strjoin(home, argv[1] + 1);
	free(tmp_str);
	return ;
}

char	*define_non_reiterative_path(char **argv, t_exec_resources *exec_resources,
	char *home)
{
	char	*final_path;
	char	*pwd;

	if (argv[1] == NULL)
	{
		final_path = ft_strdup(home); // free
		return (final_path);
	}
	if (ft_strncmp(argv[1], "/", 2) == 0)
		return (ft_strdup(argv[1]));
	if (argv[1][0] == '~' && (argv[1][1] == '/' || argv[1][1] == '\0'))
	{
		manage_tilde(argv, home);
		if (argv[1] == NULL)
			return (NULL);
	}
	if (argv[1][0] == '/')
		final_path = manage_absolute_path(argv[1]); // free
	else
	{
		if (exec_resources->pwd_present == true)
			pwd = exec_resources->local_envp[exec_resources->pwd_index];
		else
			pwd = NULL;
		final_path = manage_relative_path(argv[1], pwd); // free
	}
	return (final_path);
}

void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	free(exec_resources->user_input);
	free_cmds(exec_resources->command_list);
	ft_free_str_arr(exec_resources->local_envp);
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
