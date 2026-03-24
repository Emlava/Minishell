/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:10:32 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/24 20:35:01 by elara-va         ###   ########.fr       */
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
	struct s_pids	*next;
}	t_pids;

typedef struct s_subshell_resources
{
	t_pipes	*pipe_list;
	t_pipes	*pipe_node;
	t_pids	*pid_list;
	t_pids	*pid_node;
	t_cmd	*command_node;
}	t_subshell_resources;

// **** prompt_management/manage_prompt.c **** //
void			define_prompt(char **prompt,
					t_prompt_resources *prompt_resources,
					char **envp, char *internal_pwd);
bool			setup_prompt_home(char **prompt,
					t_prompt_resources *prompt_resources,
					char **envp);
void			construct_permanent_prompt(t_prompt_resources *prompt_resources,
					char *user, char *hostname_or_computer,
					bool free_hostname_or_computer);
void			check_permanent_prompt(t_prompt_resources *prompt_resources);

// **** define_non_reiterative_path/manage_absolute_path_utils.c **** //
char			*put_final_path_together(char **fields, int fields_count);
void			free_fields(char **fields, int fields_count);

// **** define_non_reiterative_path/manage_absolute_path.c **** //
char			*manage_absolute_path(char *requested_path);

// **** define_non_reiterative_path/define_non_reiterative_path.c **** //
char			*define_non_reiterative_path(char *requested_path,
					t_exec_resources *exec_resources, char *home);

// **** env_management/env_utils_helper.c **** //
int				replace_env_var(char **envp, int var_index,
					char *requested_var);
t_new_exports	*get_local_exp(t_new_exports **new_exports, char *name);
void			get_var_indexes_helper(t_exec_resources *exec_resources);
void			update_local_env_paths(t_exec_resources *res, char *old_pwd);
void			update_local_env_last_arg(t_exec_resources *exec_resources,
					char **argv);

// **** env_management/env_utils.c **** //
char			**duplicate_environment(char *envp[]);
void			check_essential_env_vars(t_exec_resources *exec_resources);
void			get_var_indexes(t_exec_resources *exec_resources);
char			*get_local_env(char **local_envp, char *name);
int				get_local_env_index(char **envp, char *var_name);

// **** builtins_management/ft_echo.c **** //
int				ft_echo(char **argv);

// **** builtins_management/ft_cd.c **** //
int				ft_cd(char **argv, t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** builtins_management/ft_pwd.c **** //
int				ft_pwd(char **argv, char **local_envp);

// **** builtins_management/ft_export_utils.c **** //
int				valid_identifier_check(char *requested_var);
int				create_exports_list(t_new_exports **exports_node,
					char *requested_var);
int				append_or_replace_exports_node(t_new_exports **new_exports,
					char *var_name, char *requested_var);
int				replace_exp_var(t_new_exports *preexisting_exp_var,
					char *requested_var);

// **** builtins_management/ft_export.c **** //
int				ft_export(char **argv, t_exec_resources *exec_resources);

// **** builtins_management/ft_unset.c **** //
int				ft_unset(char **argv, t_exec_resources *exec_resources);

// **** builtins_management/ft_env.c **** //
int				ft_env(char **argv, t_exec_resources *exec_resources);

// **** builtins_management/ft_exit.c **** //
int				ft_exit(char **argv, t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** builtins_management/manage_builtin.c **** //
int				manage_builtin(t_cmd *command, t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** executables_management/manage_executables.c **** //
void			run_executable(char **argv, t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources, t_pipes *pipe_list);

// **** redirection_management/redirection_management.c **** //
int				manage_redirections(t_redir *redirection_info);
int				output_redirection(t_redir *redirection_info);
int				input_redirection(t_redir *redirection_info);
int				output_redirection_append(t_redir *redirection_info);
int				heredoc_redirection(t_redir *redirection_info);

// **** command_execution/run_simple_command.c **** //
void			run_simple_command(t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** command_execution/create_pipe_and_pib_lists.c **** //
int				create_pipe_and_pib_lists(
					t_subshell_resources *subshell_resources,
					int nbr_of_children);

// **** command_execution/manage_subshell.c **** //
int				create_subshell(t_subshell_resources *resources,
					t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** command_execution/run_compound_command_utils.c **** //
int				count_commands(t_cmd *command_list);
void			close_unused_fds(t_pipes *pipe_list);
int				wait_for_all_children(t_pids *pid_list);
void			exit_dup2_failure(t_subshell_resources *subshell_resources,
					t_exec_resources *res, t_prompt_resources *prompt);

// **** command_execution/run_compound_command.c **** //
void			run_compound_command(t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

// **** cleaning/cleaning_functions.c **** //
void			free_exp_vars(t_new_exports *new_exports);
void			free_pipe_list(t_pipes *pipe_list);
void			free_pid_list(t_pids *pid_list);
void			exit_cleanup(t_exec_resources *exec_resources,
					t_prompt_resources *prompt_resources);

#endif
