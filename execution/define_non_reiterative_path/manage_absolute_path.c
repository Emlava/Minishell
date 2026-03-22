/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:29:20 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 17:50:30 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	create_and_count_fields(char ***fields, char *requested_path,
	int *fields_count)
{
	*fields = ft_split(requested_path, '/');
	if (*fields == NULL)
		return (1);
	*fields_count = 0;
	while ((*fields)[*fields_count] != NULL)
	{
		if (ft_strncmp((*fields)[*fields_count], ".", 2) == 0)
		{
			free((*fields)[*fields_count]);
			(*fields)[*fields_count] = NULL;
		}
		(*fields_count)++;
	}
	return (0);
}

static void	discard_field(char **fields, int curr_field)
{
	int	i;

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
	return ;
}

char	*manage_absolute_path(char *requested_path)
{
	char		**fields;
	int			fields_count;
	int			curr_field;
	char		*final_path;

	if (create_and_count_fields(&fields, requested_path, &fields_count) != 0)
		return (NULL);
	curr_field = 0;
	while (curr_field < fields_count)
	{
		if (fields[curr_field] != NULL
			&& ft_strncmp(fields[curr_field], "..", 3) == 0)
			discard_field(fields, curr_field);
		curr_field++;
	}
	final_path = put_final_path_together(fields, fields_count);
	free_fields(fields, fields_count);
	return (final_path);
}
