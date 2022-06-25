/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:16:59 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/25 14:48:49 by xle-baux         ###   ########.fr       */
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
			token = ignore_white_space(token);
			if (token->next == NULL || token->type != WORD)
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
