/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/24 20:31:22 by elara-va         ###   ########.fr       */
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
	char	*permanent_prompt_substr;
	bool	free_permanent_substr;
	char	*home;
	size_t	home_len;
}	t_prompt_resources;

typedef struct s_exec_resources
{
	char			**local_envp;
	bool			pwd_present;
	bool			oldpwd_present;
	bool			last_command_present;
	char			*prompt;
	char			*user_input;
	t_cmd			*command_list;
	unsigned char	curr_exit_status;
}	t_exec_resources;

// **** prompt_management/manage_prompt.c **** //
char	*get_local_env(char **local_envp, char *name);
void	check_essential_env_vars(t_exec_resources *exec_resources);
void	define_prompt(char **prompt, t_prompt_resources *prompt_resources, char **envp);
int		update_local_env_last_command(char **local_envp);
int		update_local_env_paths(char **local_envp);

// **** env_management/env_utils.c **** //
char	**duplicate_environment(char *envp[]);
char	*get_local_env(char **local_envp, char *name);

// **** prompt_management/manage_prompt_utils.c **** //
// int		determine_second_field(t_prompt *prompt_resources, bool *hostname_present);
// void	format_working_dir(t_prompt *prompt_resources, bool hostname_present);
// void	free_and_null_tmp(t_prompt *prompt_resources);
// void	free_prompt_resources(t_prompt *prompt_resources, int instance);

// **** builtins.c **** //
int		manage_builtin(t_cmd *command, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

// **** builtins_utils.c **** //
void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

#endif
