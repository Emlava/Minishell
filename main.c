/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:50:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/24 20:30:18 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	adjust_shlvl(char **envp, int shlvl_index)
{
	int		i;
	int		shlvl_int;
	char	*shlvl_str;
	char	*tmp_str;

	i = 0;
	while (envp[shlvl_index][i] && envp[shlvl_index][i] != '=')
		i++;
	if (!envp[shlvl_index][i++])
		return ;
	shlvl_int = ft_atoi(envp[shlvl_index] + i);
	if (shlvl_int > 0)
	{
		tmp_str = ft_itoa(++shlvl_int);
		shlvl_str = ft_strjoin("SHLVL=", tmp_str);
		free(tmp_str);
		if (shlvl_str)
		{
			replace_env_var(envp, shlvl_index, shlvl_str);
			free(shlvl_str);
		}
	}
	return ;
}

static int	init_shell(t_exec_resources *exec, char **envp)
{
	int	shlvl_index;

	exec->internal_pwd = getenv("PWD");
	if (!exec->internal_pwd)
	{
		ft_dprintf(2, "It seems like you naughtily removed an essential value "
			"from the parent environment.\n"
			"This shell won't run under those conditions.\n");
		return (2);
	}
	exec->internal_pwd = ft_strdup(exec->internal_pwd);
	exec->local_envp = duplicate_environment(envp);
	if (exec->local_envp == NULL)
		return (3);
	check_essential_env_vars(exec);
	get_var_indexes(exec);
	shlvl_index = get_local_env_index(exec->local_envp, "SHLVL=");
	if (shlvl_index != -1)
		adjust_shlvl(exec->local_envp, shlvl_index);
	exec->new_exports = NULL;
	exec->prompt = NULL;
	exec->curr_exit_status = 0;
	return (0);
}

static void	process_commands(t_exec_resources *ex_r, t_prompt_resources *pr_r)
{
	if (ex_r->command_list == NULL)
		return ;
	if (process_all_heredocs(ex_r->command_list, ex_r))
	{
		close(0);
		open("/dev/tty", O_RDONLY);
		return ;
	}
	if (ex_r->command_list->argv != NULL)
	{
		if (ex_r->command_list->next == NULL)
			run_simple_command(ex_r, pr_r);
		else
			run_compound_command(ex_r, pr_r);
	}
	free_cmds(ex_r->command_list);
}

static void	shell_loop(t_exec_resources *ex_r, t_prompt_resources *pr_r)
{
	while (1)
	{
		ex_r->command_list = NULL;
		if (ex_r->prompt != NULL)
			ex_r->user_input = readline(ex_r->prompt);
		else
			ex_r->user_input = readline("42_minishell: ");
		if (g_signal != 0)
		{
			ex_r->curr_exit_status = g_signal;
			g_signal = 0;
		}
		if (!ex_r->user_input)
		{
			ft_printf("exit\n");
			exit_cleanup(ex_r, pr_r);
			exit(ex_r->curr_exit_status);
		}
		add_history(ex_r->user_input);
		ex_r->command_list = start_parsing(ex_r->user_input, ex_r->local_envp,
				ex_r->new_exports, &ex_r->curr_exit_status);
		free(ex_r->user_input);
		process_commands(ex_r, pr_r);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_prompt_resources	prompt_resources;
	t_exec_resources	exec_resources;
	int					init_status;

	(void)av;
	init_signals();
	if (ac > 1)
	{
		ft_dprintf(2, "No arguments should be given at program startup.\n");
		return (1);
	}
	init_status = init_shell(&exec_resources, envp);
	if (init_status != 0)
		return (init_status);
	define_prompt(&exec_resources.prompt, &prompt_resources,
		exec_resources.local_envp, exec_resources.internal_pwd);
	shell_loop(&exec_resources, &prompt_resources);
	return (0);
}
