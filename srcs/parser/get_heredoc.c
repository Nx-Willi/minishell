/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:41:48 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/27 11:11:29 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
		close(STDIN_FILENO);
	}
}

static int	check_readline_out(char *tmp_str, char *eof)
{
	int	exit_value;

	exit_value = FALSE;
	if (!tmp_str)
	{
		printf(SH_NAME" warning: (wanted `%s\')\n", eof);
		exit_value = TRUE;
	}
	else if (_strcmp(tmp_str, eof))
	{
		free(tmp_str);
		exit_value = TRUE;
	}
	else if (_strcmp(tmp_str, "") && eof == NULL)
	{
		free(tmp_str);
		exit_value = TRUE;
	}
	return (exit_value);
}

static char	*heredoc_readline(t_infos *infos, t_token *token)
{
	char	*redir_str;
	char	*tmp_str;
	char	*eof;
	int		stdout_fd;

	eof = token->content;
	redir_str = NULL;
	signal(SIGINT, &ft_child_sig);
	stdout_fd = dup(STDIN_FILENO);
	while (g_exit_status != 130)
	{
		tmp_str = readline("> ");
		if (g_exit_status == 130 || check_readline_out(tmp_str, eof) == TRUE)
			break ;
		if (ft_strchr(tmp_str, '$') != NULL)
			tmp_str = get_env_for_heredoc(infos, tmp_str);
		redir_str = _strjoin(redir_str, tmp_str);
		redir_str = _strjoin(redir_str, "\n");
		free(tmp_str);
	}
	dup2(stdout_fd, STDIN_FILENO);
	close(stdout_fd);
	if (redir_str == NULL)
		redir_str = ft_strdup("");
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
