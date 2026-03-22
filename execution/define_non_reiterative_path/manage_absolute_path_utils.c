/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_absolute_path_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:30:21 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 17:47:52 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	append_field(bool *first_iteration, char *next_dir, char **path)
{
	char	*tmp_str;

	if (*first_iteration == false)
		next_dir = ft_strjoin("/", next_dir);
	tmp_str = *path;
	*path = ft_strjoin(*path, next_dir);
	free(tmp_str);
	if (*first_iteration == true)
		*first_iteration = false;
	else
		free(next_dir);
	return ;
}

char	*put_final_path_together(char **fields, int fields_count)
{
	char	*path;
	int		curr_field;
	bool	first_iteration;
	char	*next_dir;

	path = ft_strdup("/");
	curr_field = 0;
	first_iteration = true;
	while (curr_field < fields_count)
	{
		next_dir = find_next_dir(fields, fields_count, &curr_field);
		if (next_dir != NULL)
			append_field(&first_iteration, next_dir, &path);
		curr_field++;
	}
	return (path);
}

void	free_fields(char **fields, int fields_count)
{
	while (--fields_count >= 0)
	{
		if (fields[fields_count] != NULL)
			free(fields[fields_count]);
	}
	free(fields);
}
