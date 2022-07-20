/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:05:43 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/20 17:49:26 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*add_command(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_path = NULL;
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	return (cmd);
}

static int	count_args(t_token *token)
{
	int	i;

	i = 0;
	while (token->next && token->type != PIPE)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}

static t_token	*add_word_to_arg(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (token != NULL && token->next && token->type != PIPE)
	{
		if (token->type == WORD && token->content != NULL)
			cmd->argv[i++] = ft_strdup(token->content);
		if (token->type == GREAT || token->type == D_GREAT
			|| token->type == LESS || token->type == D_LESS)
			token = redir(token, cmd);
		else
			token = token->next;
	}
	cmd->argv[i] = NULL;
	return (token);
}

static int	fill_command(t_infos *infos, t_cmd *cmd, t_token *token)
{
	while (token->next)
	{
		cmd->argv = malloc(sizeof(char *) * (count_args(token) + 1));
		if (cmd->argv == NULL)
			return (FALSE);
		cmd->fd_in = 0;
		cmd->fdin_tmp = 0;
		cmd->fd_out = 1;
		cmd->fdout_tmp = 1;
		token = add_word_to_arg(token, cmd);
		cmd->cmd_path = get_command_path(infos, cmd->argv[0]);
		cmd->infos = infos;
		if (token != NULL && token->type == PIPE)
		{
			cmd->next = add_command(cmd);
			cmd = cmd->next;
			token = token->next;
		}
		if (token == NULL)
			return (FALSE);
	}
	return (TRUE);
}

t_cmd	*command_set(t_infos *infos, t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->prev = NULL;
	cmd->next = NULL;
	if (fill_command(infos, cmd, token) == FALSE)
		return (free_cmd(cmd), NULL);
	add_id(cmd);
	infos->npipes = count_commands(token) - 1;
	return (cmd);
}
