/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:56:18 by xle-baux          #+#    #+#             */
/*   Updated: 2022/05/26 21:10:40 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	*ft_strjoins(char *s1, char *s2)
{
	int		i;
	char	*join;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (0);
	i = -1;
	join = malloc(sizeof(char) * ((ft_strlen(s1)) + (ft_strlen(s2)) + 1));
	if (join == 0)
		return (0);
	while (s1[++i] != '\0')
		join[i] = s1[i];
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		join[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
} */

static int	check_quotes(t_token *token)
{
	int	open_quote;

	open_quote = -1;
	while (token->next)
	{
		if (token->type == QUOTE || token->type == D_QUOTE)
		{
			open_quote = token->type;
			token = token->next;
			while (token->next && token->type != open_quote)
			{
				if (token->type != DOLLAR)
					token->type = WORD;
				token = token->next;
			}
			if (!token->next)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

static int	quote_len(t_token *token, int close_quote)
{
	int	len;

	len = 0;
	while (token->type != close_quote)
	{
		len = len + ft_strlen(token->content);
		token = token->next;
	}
	return (len);
}

static char	*get_quote_char(t_token *token, int close_quote)
{
	char	*content;
	int		i;
	int		j;

//	printf("%d\n", quote_len(token, close_quote));
	content = malloc(sizeof(char) * quote_len(token, close_quote));
	if (!content)
		return (NULL);
	j = 0;
	while (token->type != close_quote)
	{
		i = 0;
		while (token->content[i])
		{
			content[j] = token->content[i];
			j++;
			i++;
		}
		token = token->next;
	}
	return (content);
}

static t_token *free_in_quote(t_token *token, int close_quote)
{
	t_token	*tmp;

	while (token->type != close_quote)
	{
		tmp = token->next;
		free(token->content);
		free(token);
		token = tmp;
	}
	if (token->type == close_quote)
	{
		tmp = token->next;
		free(token->content);
		free(token);
		token = tmp;
	}
	return (token);
}

int	join_quotes(t_token *token)
{
	int	close_quote;

	if (check_quotes(token))
		return (1);
	while (token->next)
	{
		if (token->type == QUOTE || token->type == D_QUOTE)
		{
			close_quote = token->type;
			token->type = WORD;
			free(token->content);
//			token->content = malloc(sizeof(char) * quote_len(token, close_quote));
			token->content = get_quote_char(token, close_quote);
			token->next = free_in_quote(token->next, close_quote);
		}
		token = token->next;
	}
	return (0);
}

/* int	join_quotes(t_token *token)
{
	int		open_quote;
	t_token	*tmp;

	if (check_quotes(token))
		return (1);
//	return (0);
	open_quote = -1;
	while (token->next)
	{
		if (token->type == QUOTE || token->type == D_QUOTE)
		{
			open_quote = token->type;
			token->content = "";
			token->type = WORD;
			while (token->next && token->next->type != open_quote)
			{
				if (token->next->content != NULL)
//				if (!token->next->content)
					token->content = ft_strjoin(token->content, token->next->content);
				tmp = token->next->next;
				free(token->next->content);
				free(token->next);
				token->next = tmp;
			}
			tmp = token->next->next;
			free(token->next->content);
			free(token->next);
			token->next = tmp;
		}
		if (token->next)
			token = token->next;
	}
	return (0);
} */
