/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:42:00 by xlb               #+#    #+#             */
/*   Updated: 2022/06/07 18:51:06 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_type_print(int id)
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

/* static void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		tmp = tmp->next;
		free(cmd);
		cmd = tmp;
	}
	free(cmd);
} */

int	parsing(char *input)
{
	t_token	*token;
	t_token	*token_address;
/* 	t_cmd	*cmd; */

	(void)input;
	token = get_tokens(CMD);
	token_address = token;
	dollar_format(token);
	if (join_quotes(token))
	{
		free_token(token_address);
		return (printf("syntax error: quotes"), 1);
	}
	cat_word(token);
/* 	cmd = command_set(token);
	t_cmd *cmd_address = cmd; */

	printf("\n\n---------------token-------------\n\n");
	while (token->next)
	{
		ft_printf("%s\n%s\n\n", token->content, token_type_print(token->type));
		token = token->next;
	}
	
	free_token(token_address);
	
/* 	int i = 0;
	int n = 0;
	while (cmd)
	{
		printf("\n\n---------------cammand %i-------------\n\n", n++);
		while (cmd->args[i])
		{
			printf("%s\t\ti = %i\n", cmd->args[i], i);
			i++;
		}
		cmd = cmd->next;
		i = 0;
	}
	free_cmd(cmd_address); */
	return (0);
}
