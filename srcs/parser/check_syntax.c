/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:16:59 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/19 14:40:56 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(t_token *token)
{
	token = ignore_white_space(token);
	if (token->type == PIPE)
		return (FALSE);
	while (token->next)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			token = ignore_white_space(token);
			if (token->next == NULL || token->type != WORD)
				return (FALSE);
		}
		token = token->next;
	}
	return (TRUE);
}

void	format_dollar_in_quote(t_token *token)
{
	int	inside_quote;

	inside_quote = -1;
	while (token)
	{
		if (token->next && token->type == QUOTE)
		{
			inside_quote = TRUE;
			token = token->next;
		}
		if (token->next && inside_quote == TRUE && token->type
			!= QUOTE && token->type != D_QUOTE)
		{
			token->type = WORD;
			token = token->next;
		}
		if (token->next && token->type == QUOTE)
		{
			inside_quote = FALSE;
			token = token->next;
		}
		token = token->next;
	}
}

int	check_syntax(t_token *token)
{
	if (check_pipe(token) == FALSE)
		return (printf(SH_NAME": syntax error pipe\n"), FALSE);
	return (TRUE);
}