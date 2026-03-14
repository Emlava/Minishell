/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/14 19:05:46 by elara-va         ###   ########.fr       */
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

typedef struct s_new_exports
{
	char					*var;
	struct s_new_exports	*next;
	struct s_new_exports	*prev;
}	t_new_exports;

typedef struct s_exec_resources
{
	char			**local_envp;
	t_new_exports	*new_exports;
	bool			pwd_present;
	bool			oldpwd_present;
	bool			last_arg_present;
	int				pwd_index;
	int				oldpwd_index;
	int				last_arg_index;
	char			*internal_pwd;
	char			*prompt;
	char			*user_input;
	t_cmd			*command_list;
	int				curr_exit_status;
}	t_exec_resources;

typedef struct s_pipes
{
	int				pipe[2];
	struct s_pipes	*next;
}	t_pipes;

typedef struct s_pids
{
	pid_t			pid;
	int				child_nbr;
	int				pipe_r_end;
	int				pipe_w_end;
	struct s_pids	*next;
}	t_pids;

// **** prompt_management/manage_prompt.c **** //
void			define_prompt(char **prompt, t_prompt_resources *prompt_resources, char **envp, char *internal_pwd);

// **** env_management/env_utils.c **** //
char			**duplicate_environment(char *envp[]);
void			check_essential_env_vars(t_exec_resources *exec_resources);
void			get_var_indexes(t_exec_resources *exec_resources);
char			*get_local_env(char **local_envp, char *name);
t_new_exports	*get_local_exp(t_new_exports **new_exports, char *name);
void			update_local_env_paths(t_exec_resources *exec_resources, char *new_pwd);
void			update_local_env_last_arg(t_exec_resources *exec_resources, char **argv);

// **** builtins.c **** //
int				manage_builtin(t_cmd *command, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

// **** path_management/define_non_reiterative_path.c **** //
char			*define_non_reiterative_path(char *requested_path, t_exec_resources *exec_resources,
					char *home);

// **** manage_executables.c **** //
void			run_executable(char **argv, t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** cleaning/cleaning_functions.c **** //
void			free_exp_vars(t_new_exports *new_exports);
					
// **** main.c **** //
void			free_exp_vars(t_new_exports *new_exports);
void			free_pipe_list(t_pipes *pipe_list, bool close_fds);
void			free_pid_list(t_pids *pid_list);
void			exit_cleanup(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources);

#endif
