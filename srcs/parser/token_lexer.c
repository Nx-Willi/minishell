/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:06:17 by xlb               #+#    #+#             */
/*   Updated: 2022/05/25 16:48:04 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len(char *input)
{
	char	*tok;
	int		len;

	tok = "\"'\n \t><|$\\";
	len = 0;
	if (ft_strchr(tok, (int)input[len]))
	{
		if (!ft_strncmp(">>", &input[len], 2)
			|| !ft_strncmp("<<", &input[len], 2))
			len = 2;
		else
			len = 1;
	}
	else
	{
		while (!ft_strchr(tok, input[len]))
			len++;
	}
	return (len);
}

static t_token	*add_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = 0;
	token->next = NULL;
	return (token);
}

static int	get_token_type(char *token)
{
	int					i;
	static t_token_type	types[] = {
	{"'", QUOTE},
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
	{NULL, 0}};

	i = -1;
	while (types[++i].id)
		if (!ft_strncmp(token, types[i].type, ft_strlen(token)))
			return (types[i].id);
	return (WORD);
}

t_token	*get_tokens(char *input)
{
	t_token	*token;
	t_token	*token_struct_address;
	int		i;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	i = 0;
	token_struct_address = token;
	while (input[i])
	{
		token->content = ft_substr(&input[i], 0, token_len(&input[i]));
	//	ft_strlcpy(token->content, &input[i], token_len(&input[i]) + 1);
		token->type = get_token_type(token->content);
		token->next = add_token();
		token = token->next;
		i += token_len(&input[i]);
	}
	return (token_struct_address);
}
