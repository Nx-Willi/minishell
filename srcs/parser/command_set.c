/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:05:43 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/07 17:42:02 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*add_command(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
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


t_cmd	*command_set(t_token *token)
{
	t_cmd	*cmd;
	t_cmd	*cmd_address;
	int	i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd_address = cmd;
	cmd->prev = NULL;
	cmd->next = NULL;
	while (token->next)
	{
		i = 0;
		cmd->args = malloc(sizeof(char *) * (count_args(token) + 1));
		printf("%d", count_args(token));
		if (cmd->args == NULL)
			return (NULL);
		while (token->next && token->type != PIPE)
		{
			if (token->type == WORD)
				cmd->args[i++] = ft_strdup(token->content);
			token = token->next;
		}
		cmd->args[i] = NULL;
		if (token->type == PIPE)
		{
			cmd->next = add_command(cmd);
			cmd = cmd->next;
			token = token->next;
		}
	}
	return (cmd_address);
}