/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/05 17:27:32 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **argv)
{
	int		i;
	bool	n_option;

	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		i++;
		n_option = true;
	}
	else
		n_option = false;
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
	return (0);
}

int	ft_cd(char **argv, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	char	*err_str;
	char	*final_path;

	if (argv[1] != NULL && strncmp(argv[1], ".", 2) == 0)
		return (0);
	if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (argv[1] == NULL)
		final_path = ft_strdup(prompt_resources->home); // free
	else
		final_path = define_non_reiterative_path(argv[1], exec_resources, prompt_resources->home);
	if (final_path == NULL)
	{
		ft_dprintf(2, "minishell: cd: failed to manage path because of a malloc() failure\n");
		return (2);
	}
	if (chdir(final_path) == -1)
	{
		err_str = ft_strjoin("minishell: cd: ", argv[1]); // free
		free(final_path);
		if (err_str != NULL)
		{
			perror(err_str);
			free(err_str);
		}
		return (3);
	}
	if (exec_resources->pwd_present == true)
		update_local_env_paths(exec_resources, final_path);
	free(final_path);
	if (exec_resources->prompt != NULL)
		define_prompt(&exec_resources->prompt, prompt_resources, exec_resources->local_envp);
	return (0);
}

int	ft_pwd(char **argv, char **local_envp)
{
	char	*working_dir;

	if (argv[1] != NULL && argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: pwd: no options for this builtin\n");
		return (1);
	}
	working_dir = get_local_env(local_envp, "PWD");
	if (working_dir == NULL)
		return (2);
	printf("%s\n", working_dir);
	return (0);
}

static int	valid_identifier_check(char *requested_var)
{
	int	i;

	i = 0;
	if (ft_isdigit(requested_var[i]) || requested_var[i] == '=')
		return (1);
	while (requested_var[i])
	{
		if (!ft_isalnum(requested_var[i]) && requested_var[i] != '_'
			&& requested_var[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_var(char *requested_var, char **envp, t_new_exports **new_exports)
{
	int				i;
	char			*var_name;
	char			*preexisting_env_var;
	t_new_exports	*curr_exp_var;
	t_new_exports	*preexisting_exp_var;

	i = 0;
	while (requested_var[i] != '=')
		i++;
	var_name = malloc(sizeof(char) * (i + 1)); // free
	if (!var_name)
		return (1);
	ft_strlcpy(var_name, requested_var, i + 1);
	//
	printf("var_name: %s\n", var_name);
	//
	preexisting_env_var = get_local_env(envp, var_name);
	if (preexisting_env_var != NULL)
	{
		preexisting_env_var -= (ft_strlen(var_name) + 1);
		free(var_name);
		free(preexisting_env_var);
		preexisting_env_var = ft_strdup(requested_var);
		if (preexisting_env_var == NULL)
			return (2);
		return (0);
	}
	if (*new_exports == NULL)
	{
		free(var_name);
		*new_exports = malloc(sizeof(t_new_exports)); // free
		if (*new_exports == NULL)
			return (3);
		(*new_exports)->var = ft_strdup(requested_var); // free
		if ((*new_exports)->var == NULL)
			return (4);
		(*new_exports)->next = NULL;
	}
	else
	{
		curr_exp_var = *new_exports;
		preexisting_exp_var = get_local_exp(new_exports, var_name);
		free(var_name);
		if (preexisting_exp_var == NULL)
		{
			while (curr_exp_var->next != NULL)
				curr_exp_var = curr_exp_var->next;
			curr_exp_var->next = malloc(sizeof(t_new_exports)); // free
			curr_exp_var = curr_exp_var->next;
			if (curr_exp_var == NULL)
				return (5);
			curr_exp_var->var = ft_strdup(requested_var);
			if (curr_exp_var->var == NULL)
				return (6);
			curr_exp_var->next = NULL;
		}
		else
		{
			free(preexisting_exp_var->var);
			preexisting_exp_var->var = ft_strdup(requested_var); // free
			if (preexisting_exp_var->var == NULL)
				return (7);
		}
	}
	return (0);
}

// ft_export() will immediately stop exporting if an invalid identifier is found
// or if an error occurs.
int	ft_export(char **argv, char **envp, t_new_exports **new_exports)
{
	int				i;

	if (argv[1] == NULL)
	{
		ft_dprintf(2, "minishell: export: argument needed\n");
		return (1);
	}
	if (argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: export: %s: no options for this builtin\n", argv[1]);
		return (2);
	}
	i = 1;
	while (argv[i])
	{
		if (valid_identifier_check(argv[i]) == 1)
		{
			ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", argv[i]);
			return (3);
		}
		if (ft_strchr(argv[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		if (export_var(argv[i], envp, new_exports) != 0)
		{
			ft_dprintf(2, "minishell: export: %s: failed to export variable\n");
			return (4);
		}
		i++;
	}
	return (0);
}

int	ft_env(char **argv, char **envp, t_new_exports *new_exports, int last_arg_index)
{
	int	i;

	if (argv[1] != NULL)
	{
		ft_dprintf(2, "minishell: env: no options for this builtin\n");
		return (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (i != last_arg_index)
			printf("%s\n", envp[i]);
		i++;
	}
	while (new_exports != NULL)
	{
		printf("%s\n", new_exports->var);
		new_exports = new_exports->next;
	}
	printf("%s\n", envp[last_arg_index]);
	return (0);
}

int	ft_exit(char **argv, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	int	exit_status;

	// if piping was implemented, we manage things differently
	printf("exit\n");
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		if (!ft_is_numeric_str(argv[1]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric arguments required\n", argv[1]);
			exit_status = 2;
		}
		else
			exit_status = ft_atoi(argv[1]);
	}
	else
		exit_status = exec_resources->curr_exit_status;
	exit_cleanup(exec_resources, prompt_resources);
	exit(exit_status);
}

int	manage_builtin(t_cmd *command, t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	if (command->builtin == BUILTIN_ECHO)
		return (ft_echo(command->argv));
	if (command->builtin == BUILTIN_CD)
		return (ft_cd(command->argv, exec_resources, prompt_resources));
	if (command->builtin == BUILTIN_PWD)
		return (ft_pwd(command->argv, exec_resources->local_envp));
	if (command->builtin == BUILTIN_EXPORT)
		return (ft_export(command->argv, exec_resources->local_envp, &exec_resources->new_exports));
	// if (command->builtin == BUILTIN_UNSET)
	// 	return (ft_unset(command->argv));
	if (command->builtin == BUILTIN_ENV)
		return (ft_env(command->argv, exec_resources->local_envp,
			exec_resources->new_exports, exec_resources->last_arg_index));
	else
		return (ft_exit(command->argv, exec_resources, prompt_resources));
}

// Things to free or close:
// ft_cd():
// 	-err_str
// 	-dirp (close)
// ft_pdw():
// 	-working_dir
