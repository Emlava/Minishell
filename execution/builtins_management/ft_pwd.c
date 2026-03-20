/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:33:12 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 17:33:48 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
