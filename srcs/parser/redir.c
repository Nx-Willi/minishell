/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:37:56 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/26 21:51:07 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_great_files(t_token *token, t_cmd *cmd)
{
	while (token->type == GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '>'\n"), NULL);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

static t_token	*create_d_great_files(t_token *token, t_cmd *cmd)
{
	while (token->type == D_GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '>>'\n"), NULL);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open(token->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

t_token	*redir(t_token *token, t_cmd *cmd)
{
	if (token->type == GREAT)
		token = create_great_files(token, cmd);
	else if (token->type == D_GREAT)
		token = create_d_great_files(token, cmd);
	if (token == NULL)
		return (NULL);
	return (token);
}
