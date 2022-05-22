/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlb <xlb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:06:17 by xlb               #+#    #+#             */
/*   Updated: 2022/05/21 20:39:10 by xlb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pair_of_quotes(char *input)
{
	int i;
	int quote_count;
	int double_quote_count;

	i = 0;
	quote_count = 0;
	double_quote_count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			quote_count++;
		if (input[i] == '\"')
			double_quote_count++;
		i++;
	}
	if ((quote_count % 2 == 1) || (double_quote_count % 2 == 1))
		return (1);
	return (0);
}

static t_token *add_token(void)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = 0;
	token->next = NULL;
	return (token);
}

static int get_token_type(char *token)
{
	int				i;

	t_token_type types[] = {{"'", QUOTE},
			{"\"", D_QUOTE},
			{"\n", NLINE},
			{" ", WHITE_SPACE},
			{">", GREAT},
			{">>", D_GREAT},
			{"<", LESS},
			{"<<", D_LESS},
			{"|", PIPE},
			{"$", DOLLAR},
			{"\\", BACKSLASH},
			{NULL, 0}
			};
	i = 0;
	while (types[i].id)
	{
		if (!ft_strncmp(token, types[i].type, ft_strlen(token)))
			return (types[i].id);
		i++;
	}
	return (WORD);
}

t_token *get_tokens(char *input)
{
	t_token *token;
	t_token	*token_struct_address;
	char **clean_token_char;

	if (check_pair_of_quotes(input))
		return (ft_printf("syntax error: quotes\n"), NULL);
	clean_token_char = ft_split(input, ' ');
	int i = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token_struct_address = token;
	while (clean_token_char[i])
	{
		token->content = clean_token_char[i];
		token->type = get_token_type(clean_token_char[i]);
		token->next = add_token();
		token = token->next;
		i++;
	}
	return (token_struct_address);
}

//