/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:42:00 by xlb               #+#    #+#             */
/*   Updated: 2022/06/30 18:35:34 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
	{
		if (token->type != 0)
			free(tmp->content);
		tmp = tmp->next;
		free(token);
		token = tmp;
	}
	free(tmp);
}

t_cmd	*parsing(t_infos *infos, char *input)
{
	t_token	*token;
	t_token	*token_address;
	t_cmd	*cmd;

	token = get_tokens(input);
	token_address = token;
	dollar_format(infos, token);
	if (join_quotes(token))
		return (free_token(token_address), NULL);
	cat_word(token);
	if (check_syntax(token) == FALSE)
		return (free_token(token_address), NULL);
	print_token_struct(token);
	cmd = command_set(infos, token);
<<<<<<< HEAD
	if (cmd == NULL)
		return (NULL);
=======
>>>>>>> wdebotte
	free_token(token_address);
	print_cmd_struct(cmd);
	return (cmd);
}
