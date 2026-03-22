/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_and_pib_lists.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 14:41:41 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 16:52:42 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	initialize_pipe_node(t_pipes **pipe_node)
{
	*pipe_node = malloc(sizeof(t_pipes));
	if (!*pipe_node)
		return (1);
	(*pipe_node)->next = NULL;
	if (pipe((*pipe_node)->pipe) == -1)
		return (2);
	return (0);
}

static int	initialize_pid_node(t_pids **pid_node, int child_count)
{
	*pid_node = malloc(sizeof(t_pids));
	if (!*pid_node)
		return (1);
	(*pid_node)->pid = -1;
	(*pid_node)->child_nbr = child_count;
	(*pid_node)->next = NULL;
	return (0);
}

static int	initialize_heads(t_pipes **pipe_list, t_pids **pid_list,
	int child_count)
{
	if (initialize_pipe_node(pipe_list) != 0)
		return (1);
	if (initialize_pid_node(pid_list, child_count) != 0)
		return (2);
	return (0);
}

static int	initialize_next_nodes(t_subshell_resources *subshell_resources,
	int child_count, int nbr_of_children)
{
	if (child_count < nbr_of_children)
	{
		if (initialize_pipe_node(&subshell_resources->pipe_node->next) != 0)
			return (1);
		subshell_resources->pipe_node = subshell_resources->pipe_node->next;
	}
	if (initialize_pid_node(&subshell_resources->pid_node->next,
			child_count) != 0)
		return (2);
	subshell_resources->pid_node = subshell_resources->pid_node->next;
	return (0);
}

int	create_pipe_and_pib_lists(t_subshell_resources *subshell_resources,
	int nbr_of_children)
{
	int		child_count;

	child_count = 1;
	if (initialize_heads(&subshell_resources->pipe_list,
			&subshell_resources->pid_list, child_count) != 0)
		return (1);
	subshell_resources->pipe_node = subshell_resources->pipe_list;
	subshell_resources->pid_node = subshell_resources->pid_list;
	while (++child_count <= nbr_of_children)
	{
		if (initialize_next_nodes(subshell_resources, child_count,
				nbr_of_children) != 0)
		{
			free_pipe_list(subshell_resources->pipe_list);
			free_pid_list(subshell_resources->pid_list);
			return (2);
		}
	}
	subshell_resources->pipe_node = subshell_resources->pipe_list;
	subshell_resources->pid_node = subshell_resources->pid_list;
	return (0);
}
