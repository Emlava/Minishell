/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/21 22:35:26 by elara-va         ###   ########.fr       */
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
# include "../parsing/parsing.h"
# include "../libft/libft.h"

typedef struct s_prompt_resources
{
	char	**envp;
	char	*user;
	char	*host_or_computer;
	char	*working_dir;
	char	*tmp;
	bool	curr_computer_present;
}	t_prompt;

typedef struct s_resources
{
	char			**local_envp;
	char			*prompt;
	char			*user_input;
	t_cmd			*command_list;
	unsigned char	curr_exit_status;
}	t_resources;

// **** prompt_management/manage_prompt.c **** //
char	*get_local_env(char **local_envp, char *name);
void	define_prompt(char **prompt, char **local_envp);

// **** prompt_management/manage_prompt_utils.c **** //
int		determine_second_field(t_prompt *prompt_resources, bool *hostname_present);
void	format_working_dir(t_prompt *prompt_resources, bool hostname_present);
void	free_and_null_tmp(t_prompt *prompt_resources);
void	free_prompt_resources(t_prompt *prompt_resources, int instance);

// **** builtins.c **** //
int		manage_builtin(t_cmd *command, t_resources *resources);

// **** builtins_utils.c **** //
int		update_local_environment(char **local_envp);
void	exit_cleanup(t_resources *resources);

#endif
