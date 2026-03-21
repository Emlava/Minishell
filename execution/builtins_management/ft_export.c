/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:30:35 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 20:56:48 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	export_var(char *requested_var, char **envp,
	t_new_exports **new_exports)
{
	int				i;
	char			*var_name;
	char			*preexisting_env_var;
	int				return_value;

	i = 0;
	while (requested_var[i] != '=')
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (1);
	ft_strlcpy(var_name, requested_var, i + 1);
	preexisting_env_var = get_local_env(envp, var_name);
	if (preexisting_env_var != NULL)
		return (replace_env_var(preexisting_env_var, var_name, requested_var));
	if (*new_exports == NULL)
	{
		free(var_name);
		return_value = create_exports_list(new_exports, requested_var);
	}
	else
		return_value = append_or_replace_exports_node(new_exports,
				var_name, requested_var);
	return (return_value);
}

static int	process_requested_var(char *requested_var, char **envp,
	t_new_exports **new_exports)
{
	if (valid_identifier_check(requested_var) == 1)
	{
		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n",
			requested_var);
		return (3);
	}
	if (ft_strchr(requested_var, '=') == NULL)
		return (0);
	if (export_var(requested_var, envp, new_exports) != 0)
	{
		ft_dprintf(2, "minishell: export: %s: failed to export variable\n");
		return (4);
	}
	return (0);
}

// ft_export() will immediately stop exporting if an invalid identifier is found
// or if an error occurs.
int	ft_export(char **argv, char **envp, t_new_exports **new_exports)
{
	int	i;
	int	return_value;

	if (argv[1] == NULL)
	{
		// print everything but $_
		ft_dprintf(2, "minishell: export: argument needed\n");
		return (1);
	}
	if (argv[1][0] == '-')
	{
		ft_dprintf(2, "minishell: export: %s: no options for this builtin\n",
			argv[1]);
		return (2);
	}
	i = 1;
	while (argv[i])
	{
		return_value = process_requested_var(argv[i], envp, new_exports);
		if (return_value != 0)
			return (return_value);
		i++;
	}
	return (0);
}
