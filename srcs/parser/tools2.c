/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:57:24 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/23 16:58:05 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

t_token	*exit_status_check(t_token *token)
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

t_token	*ignore_white_space(t_token *token)
{
	while (token->type == WHITE_SPACE)
		token = token->next;
	return (token);
}

int	env_len_size(t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i] != '\0' && (ft_isalpha(token->content[i]) != 0
			|| ft_isalnum(token->content[i]) != 0 || token->content[i] == '_'))
		i++;
	return (i);
}
