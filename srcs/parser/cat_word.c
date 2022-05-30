/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:45 by xle-baux          #+#    #+#             */
/*   Updated: 2022/05/30 17:43:43 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cat_word(t_token *token)
{
	t_token *tmp;
	
	while (token->next)
	{
		if (token->next && token->type == WORD)
		{
			while (token->next && token->next->type == WORD)
			{
				if (token->next->content != NULL)
					token->content = _strjoin(token->content, token->next->content);
				tmp = token->next->next;
				free(token->next->content);
				free(token->next);
				token->next = tmp;
			}
		}
		token = token->next;
	}
}
