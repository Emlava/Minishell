/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:25:10 by hudescam          #+#    #+#             */
/*   Updated: 2026/02/23 13:38:44 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static void print_tokens(t_token *t)
// {
//     while (t)
//     {
//         if (t->type == TOKEN_WORD)
//             ft_printf("WORD(%s)\n", t->value);
//         else if (t->type == TOKEN_PIPE)
//             ft_printf("PIPE\n");
//         else if (t->type == TOKEN_REDIR_IN)
//             ft_printf("REDIR_IN\n");
//         else if (t->type == TOKEN_REDIR_OUT)
//             ft_printf("REDIR_OUT\n");
//         else if (t->type == TOKEN_REDIR_APPEND)
//             ft_printf("REDIR_APPEND\n");
//         else if (t->type == TOKEN_HEREDOC)
//             ft_printf("HEREDOC\n");
//         t = t->next;
//     }
// }

// static void	print_cmds(t_cmd *cmd)
// {
// 	t_redir	*tmp;
// 	int		i;

// 	while (cmd)
// 	{
// 		ft_printf("=== COMMAND ===\n");
// 		i = 0;
// 		while (cmd->argv && cmd->argv[i])
// 		{
// 			ft_printf("ARG: %s\n", cmd->argv[i]);
// 			i++;
// 		}
// 		tmp = cmd->redirs;
// 		while (tmp)
// 		{
// 			ft_printf("REDIR type: %d target: %s quoted: %d\n",
// 				tmp->type, tmp->target, tmp->quoted);
// 			tmp = tmp->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }

t_cmd	*start_parsing(char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!line)
		return (NULL);
	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	if (!check_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	return (cmds);
}

// int	main(void)
// {
// 	char	*line;
// 	t_token	*tokens;
// 	t_cmd	*cmds;

// 	init_signals();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			ft_printf("exit\n");
// 			break ;
// 		}
// 		tokens = lexer(line);
// 		if (tokens && check_syntax(tokens))
// 		{
// 			cmds = parse_tokens(tokens);
// 			print_cmds(cmds);
// 			free_cmds(cmds);
// 		}
// 		free_tokens(tokens);
// 		free(line);
// 	}
// 	return (0);
// }
