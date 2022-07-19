/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:37:56 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/19 15:43:43 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_great_files(t_token *token, t_cmd *cmd)
{
	while (token->type == GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
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
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = open(token->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

static t_token	*get_less_files(t_token *token, t_cmd *cmd)
{
	while (token->type == LESS)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = open(token->content, O_RDONLY);
		if (cmd->fd_in == -1)
			return (printf(SH_NAME": %s: No such file or directory\n",
					token->content), NULL);
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
	else if (token->type == LESS)
		token = get_less_files(token, cmd);
	else if (token->type == D_LESS)
		token = get_heredoc(token);
	if (token == NULL)
		return (NULL);
	return (token);
}
