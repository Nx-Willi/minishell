/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:42:00 by xlb               #+#    #+#             */
/*   Updated: 2022/05/25 15:05:23 by xle-baux         ###   ########.fr       */
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

int parsing(char *input)
{
	t_token *token;
	
	input = "ls -la | grep \"$P\'A\'TH\" | wc -l >> test.txt";
	token = get_tokens(input);
	if (clean_quotes(token))
		return (printf("syntax error: quotes"), 1);
	while (token->next)
	{
		ft_printf("%s\t%s\n\n", token->content, token_type_print(token->type));
		token = token->next;
	}
	return (0);
}