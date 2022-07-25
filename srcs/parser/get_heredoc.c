/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:41:48 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/25 15:19:22 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static char	*heredoc_readline(t_infos *infos, t_token *token)
{
	char	*redir_str;
	char	*tmp_str;
	char	*eof;

	eof = token->content;
	redir_str = NULL;
	while (1)
	{
		tmp_str = NULL;
		tmp_str = readline("> ");
		if (_strcmp(tmp_str, eof))
		{
			free(tmp_str);
			break ;
		}
		if (ft_strchr(tmp_str, '$') != NULL)
			tmp_str = get_env_for_heredoc(infos, tmp_str);
		redir_str = _strjoin(redir_str, tmp_str);
		redir_str = _strjoin(redir_str, "\n");
		free(tmp_str);
	}
	return (redir_str);
}

t_token	*get_heredoc(t_infos *infos, t_token *token, t_cmd *cmd)
{
	char	*redir_str;
	int		fd[2];

	if (pipe(fd) == -1)
		return (NULL);
	token = token->next;
	token = ignore_white_space(token);
	redir_str = heredoc_readline(infos, token);
	write(fd[1], redir_str, ft_strlen(redir_str));
	free(redir_str);
	close(fd[1]);
	cmd->fd_in = fd[0];
	token = token->next;
	token = ignore_white_space(token);
	return (token);
}
