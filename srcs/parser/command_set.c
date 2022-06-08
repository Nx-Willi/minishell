/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:05:43 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/08 19:29:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*add_command(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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

static int	fill_command(t_cmd *cmd, t_token *token)
{
	int	i;

	while (token->next)
	{
		i = 0;
		cmd->argv = malloc(sizeof(char *) * (count_args(token) + 1));
		if (cmd->argv == NULL)
			return (1);
		while (token->next && token->type != PIPE)
		{
			if (token->type == WORD)
				cmd->argv[i++] = ft_strdup(token->content);
			token = token->next;
		}
		cmd->argv[i] = NULL;
		if (token->type == PIPE)
		{
			cmd->next = add_command(cmd);
			cmd = cmd->next;
			token = token->next;
		}
	}
	return (0);
}

t_cmd	*command_set(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->prev = NULL;
	cmd->next = NULL;
	if (fill_command(cmd, token))
		return (NULL);
	return (cmd);
}
