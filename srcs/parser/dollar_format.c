/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:59:57 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/14 09:37:10 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static t_token	*exit_status_check(t_token *token)
{
	t_token	*tmp;

	token->type = WORD;
	tmp = token->next->next;
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	token->content[0] = g_exit_status + '0';
	return (token);
}

static t_token	*get_env(t_infos *infos, t_token *token)
{
	t_token	*tmp;

	tmp = token->next->next;
	free (token->content);
	if (get_env_var_value(infos, token->next->content) != NULL)
	{
		token->content = ft_strdup(get_env_var_value(infos,
					token->next->content));
		token->type = WORD;
	}
	else
	{
		token->content = NULL;
		token->type = 0;
	}
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	return (token);
}

void	dollar_format(t_infos *infos, t_token *token)
{
	while (token != NULL)
	{
		if (token->type == DOLLAR && (token->next->type == 0
				|| token->next->type == WHITE_SPACE))
			token->type = WORD;
		else if (token->type == DOLLAR && _strcmp(token->next->content, "?"))
			token = exit_status_check(token);
		else if (token->type == DOLLAR)
			token = get_env(infos, token);
		token = token->next;
	}
}
