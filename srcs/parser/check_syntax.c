/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:16:59 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/23 13:32:15 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(t_token *token)
{
	while (token->next)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			while (token->type == SPACE)
				token = token->next;
			if (token->next == NULL || token->next->type != WORD)
				return (FALSE);
		}
		token = token->next;
	}
	return (TRUE);
}

int	check_syntax(t_token *token)
{
	if (check_pipe(token) == FALSE)
		return (printf(SH_NAME": syntax error pipe\n"), FALSE);
	return (TRUE);
}
