/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:59:57 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/17 22:05:07 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static t_token	*exit_status_check(t_token *token)
{
	t_token	*tmp;

	token->type = WORD;
	tmp = token->next->next;
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	free(token->content);
	token->content = ft_itoa(g_exit_status);
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
		if (token->type == DOLLAR && _strcmp(token->next->content, "?"))
			token = exit_status_check(token);
		else if (token->type == DOLLAR && (token->next->type == 0
				|| token->next->type == WHITE_SPACE
				|| token->next->type == QUOTE
				|| token->next->type == D_QUOTE))
			token->type = WORD;
		else if (token->type == DOLLAR)
			token = get_env(infos, token);
		token = token->next;
	}
}
