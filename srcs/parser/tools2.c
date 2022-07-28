/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:57:24 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/28 13:49:24 by xle-baux         ###   ########.fr       */
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

t_token	*fill_split_to_tokens(t_token *token, char **split_content)
{
	int	i;

	i = 1;
	while (split_content[i])
	{
		token->next = add_token();
		token = token->next;
		token->content = ft_strdup(" ");
		token->type = WHITE_SPACE;
		token->next = add_token();
		token = token->next;
		token->content = ft_strdup(split_content[i++]);
		token->type = WORD;
	}
	return (token);
}
