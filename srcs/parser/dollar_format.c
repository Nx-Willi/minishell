/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:59:57 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/21 17:17:04 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	env_len_size(t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i] != '\0' && (ft_isalpha(token->content[i]) != 0
			|| ft_isalnum(token->content[i]) != 0 || token->content[i] == '_'))
		i++;
	return (i);
}

static t_token	*fill_new_token(t_token *token, char *tmp_content, int env_len)
{
	int		i;
	t_token	*tmp_next;

	i = -1;
	tmp_next = token->next->next;
	token->next->next = add_token();
	token->next->next->type = WORD;
	token->next->next->content = malloc(sizeof(char)
			* (ft_strlen(tmp_content) - env_len) + 1);
	if (token->next->next->content == NULL)
		return (NULL);
	while (tmp_content[++i + env_len])
		token->next->next->content[i] = tmp_content[i + env_len];
	token->next->next->content[i] = '\0';
	token->next->next->next = tmp_next;
	free(tmp_content);
	return (token);
}

static t_token	*clean_env(t_token *token)
{
	int		env_len;
	int		i;
	char	*tmp_content;

	env_len = env_len_size(token->next);
	i = -1;
	tmp_content = ft_strdup(token->next->content);
	free(token->next->content);
	token->next->content = malloc(sizeof(char) * (env_len + 1));
	if (token->next->content == NULL)
		return (NULL);
	while (++i < env_len)
		token->next->content[i] = tmp_content[i];
	token->next->content[i] = '\0';
	token = fill_new_token(token, tmp_content, env_len);
	if (token == NULL)
		return (NULL);
	return (token);
}

static t_token	*get_env(t_infos *infos, t_token *token)
{
	t_token	*tmp;

	token = clean_env(token);
	tmp = token->next->next;
	free (token->content);
	if (get_env_var_value(infos, token->next->content) != NULL)
	{
		token->content = ft_strdup(get_env_var_value(infos,
					token->next->content));
		token->type = WORD;
	}
	else
	{
		token->content = NULL;
		token->type = 0;
	}
	free(token->next->content);
	free(token->next);
	token->next = tmp;
	return (token);
}

void	dollar_format(t_infos *infos, t_token *token)
{
	while (token != NULL)
	{
		if (token->type == DOLLAR && _strcmp(token->next->content, "?"))
			token = exit_status_check(token);
		else if (token->type == DOLLAR && (token->next->type == 0
				|| token->next->type == WHITE_SPACE
				|| token->next->type == QUOTE
				|| token->next->type == D_QUOTE))
			token->type = WORD;
		else if (token->type == DOLLAR)
			token = get_env(infos, token);
		token = token->next;
	}
}
