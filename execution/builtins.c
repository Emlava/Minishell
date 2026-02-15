/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:14:19 by elara-va          #+#    #+#             */
/*   Updated: 2026/02/15 21:10:17 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_builtin(char **argv, int prev_exit_status)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (ft_echo(argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (ft_cd(argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (ft_pwd(argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (ft_export(argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (ft_unset(argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (ft_env(argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
	{
		// clean_up(things to free or close);
		exit(prev_exit_status);
	}
}
