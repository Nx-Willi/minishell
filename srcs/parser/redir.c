/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:37:56 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/25 17:58:20 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_files(t_token *token, t_cmd *cmd)
{
	while (token->type == GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '>'\n"), NULL);
		cmd->fd_out = open(token->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

t_token	*redir(t_token *token, t_cmd *cmd)
{
	token = create_files(token, cmd);
	return (token);
}
