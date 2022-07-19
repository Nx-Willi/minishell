/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:00 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/19 15:06:25 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*check_great_files(t_token *token)
{
	while (token->type == GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '>'\n"), NULL);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

static t_token	*check_d_great_files(t_token *token)
{
	while (token->type == D_GREAT)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '>>'\n"), NULL);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

static t_token	*check_less_files(t_token *token)
{
	while (token->type == LESS)
	{
		token = token->next;
		token = ignore_white_space(token);
		if (token->type != WORD)
			return (printf(SH_NAME": syntax error redirection '<'\n"), NULL);
		token = token->next;
		token = ignore_white_space(token);
	}
	return (token);
}

int	check_redir(t_token *token)
{
	while (token)
	{
		if (token->type == GREAT)
			token = check_great_files(token);
		else if (token->type == D_GREAT)
			token = check_d_great_files(token);
		else if (token->type == LESS)
			token = check_less_files(token);
		if (token == NULL)
			return (FALSE);
		else
			token = token->next;
	}
	return (TRUE);
}
