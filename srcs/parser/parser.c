/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:42:00 by xlb               #+#    #+#             */
/*   Updated: 2022/05/25 16:59:08 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char* token_type_print(int id)
{
	if (id == 0)
		return ("NULL");
	if (id == 1)
		return ("WORD");
	if (id == 2)
		return ("QUOTE");
	if (id == 3)
		return ("D_QUOTE");
	if (id == 4)
		return ("NLINE");
	if (id == 5)
		return ("WHITE_SPACE");
	if (id == 6)
		return ("GREAT");
	if (id == 7)
		return ("D_GREAT");
	if (id == 8)
		return ("LESS");
	if (id == 9)
		return ("D_LESS");
	if (id == 10)
		return ("PIPE");
	if (id == 11)
		return ("DOLLAR");
	if (id == 12)
		return ("BACKSLASH");
	return (NULL);
}

static void	free_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp->next)
	{
		if (tmp->type != DOLLAR)
			free(tmp->content);
		tmp = tmp->next;
		free(token);
		token = tmp;
	}
	free(tmp);
}

int parsing(char *input)
{
	t_token *token;
	t_token *token_address;
	
//	input = "ls -la | grep $TESTENV | \"wc -l >> test.txt\"";
	input = "cat $TESTENV";
	token = get_tokens(input);
	token_address = token;
	dollar_format(token);
	if (clean_quotes(token))
		return (printf("syntax error: quotes"), 1);
	while (token->next)
	{
		ft_printf("%s\t%s\n\n", token->content, token_type_print(token->type));
		token = token->next;
	}
	free_token(token_address);
	return (0);
}