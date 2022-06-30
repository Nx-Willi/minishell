/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:59:57 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/30 19:07:45 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_format(t_infos *infos, t_token *token)
{
	t_token	*tmp;

	while (token->next)
	{
		if (token->type == DOLLAR)
		{
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
		}
		token = token->next;
	}
}
