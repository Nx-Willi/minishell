/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:56:18 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/28 14:48:53 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(t_token *token)
{
	int	open_quote;

	open_quote = -1;
	while (token->next)
	{
		if (token->type == QUOTE || token->type == D_QUOTE)
		{
			open_quote = token->type;
			token = token->next;
			while (token->next && token->type != open_quote)
			{
				if (token->type != DOLLAR)
					token->type = WORD;
				token = token->next;
			}
			if (!token->next)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

static t_token	*empty_quotes(t_token *token)
{
	t_token	*tmp;

	free(token->content);
	token->content = ft_strdup("\0");
	token->type = WORD;
	tmp = token->next->next;
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	return (token);
}

static t_token	*clean_quotes(t_token *token, int open_quote)
{
	t_token	*tmp;

	open_quote = token->type;
	free(token->content);
	token->content = NULL;
	token->type = WORD;
	while (token->next && token->next->type != open_quote)
	{
		if (token->next->content != NULL)
			token->content = _strjoin(token->content, token->next->content);
		tmp = token->next->next;
		if (token->next->type != DOLLAR)
			free(token->next->content);
		free(token->next);
		token->next = tmp;
	}
	if (token->content == NULL)
		token->type = 0;
	tmp = token->next->next;
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	return (token);
}

int	join_quotes(t_token *token)
{
	int		open_quote;

	if (check_quotes(token))
		return (printf(SH_NAME": syntax error quotes\n"), 1);
	open_quote = -1;
	while (token->next)
	{
		if ((token->type == QUOTE || token->type == D_QUOTE)
			&& (token->type == token->next->type))
			token = empty_quotes(token);
		else if (token->type == QUOTE || token->type == D_QUOTE)
		{
			open_quote = token->type;
			token = clean_quotes(token, open_quote);
		}
		if (token->next)
			token = token->next;
	}
	return (0);
}
