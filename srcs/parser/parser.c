/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlb <xlb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:42:00 by xlb               #+#    #+#             */
/*   Updated: 2022/05/21 20:39:49 by xlb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(char *input)
{
	t_token *token;
	
	input = "ls -'la' | g'rep \"toto tata\" | wc -l";
	token = get_tokens(input);
	while (token->next)
	{
		ft_printf("%s\t%i\n\n", token->content, token->type);
		token = token->next;
	}
	return (0);
}