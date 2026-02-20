/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/20 12:29:22 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct s_prompt_resources
{
	char	*user;
	char	*host_or_computer;
	char	*working_dir;
	char	*tmp;
	bool	hostname_present;
	bool	curr_computer_present;
}	t_prompt;

// **** prompt_management/manage_prompt.c **** //
void	define_prompt(char **prompt);

// **** prompt_management/manage_prompt_utils.c **** //
int		determine_second_field(t_prompt *prompt_resources);
void	format_working_dir(t_prompt *prompt_resources);
void	free_and_null_tmp(t_prompt *prompt_resources);
void	free_prompt_resources(t_prompt *prompt_resources, int instance);

// **** builtins.c **** //
int		manage_builtin(char **argv, int prev_exit_status, char **prompt);

#endif
