/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/26 13:51:33 by elara-va         ###   ########.fr       */
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
	int				pwd_index;
	int				oldpwd_index;
	int				last_command_index;
	char			*prompt;
	char			*user_input;
	t_cmd			*command_list;
	unsigned char	curr_exit_status;
}	t_exec_resources;

// **** prompt_management/manage_prompt.c **** //
void	define_prompt(char **prompt, t_prompt_resources *prompt_resources, char **envp);

// **** env_management/env_utils.c **** //
char	**duplicate_environment(char *envp[]);
void	check_essential_env_vars(t_exec_resources *exec_resources);
void	get_var_indexes(t_exec_resources *exec_resources);
char	*get_local_env(char **local_envp, char *name);
void	update_local_env_paths(t_exec_resources *exec_resources);
void	update_local_env_last_command(t_exec_resources *exec_resources);

// **** prompt_management/manage_prompt_utils.c **** //
// int		determine_second_field(t_prompt *prompt_resources, bool *hostname_present);
// void	format_working_dir(t_prompt *prompt_resources, bool hostname_present);
// void	free_and_null_tmp(t_prompt *prompt_resources);
// void	free_prompt_resources(t_prompt *prompt_resources, int instance);

// **** builtins.c **** //
int		manage_builtin(t_cmd *command, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

// **** builtins_utils.c **** //
void	define_non_reiterative_path(char **argv);
void	exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

#endif
