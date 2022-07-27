/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:59:57 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/27 17:56:39 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	format_dollar_in_quote(t_token *token)
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

static t_token	*fill_new_token(t_token *token, char *tmp_content, int env_len) // First token type is DOLLAR ($)
																				// tmp_token = TEST=toto
																				// env_len = ft_strlen(TEST)
{
	int		i;
	t_token	*tmp_next;

	i = -1;
	tmp_next = token->next->next; // Copy token->next->next to tmp_next (token after TEST=toto, frmm now we'll name it token = ULTIM)
	token->next->next = add_token(); // Add a new token between TEST=toto and ULTIM (frmm now we'll name it token = NEWTOK)
	token->next->next->type = WORD; // NEWTOK token->typr = WORD;
	token->next->next->content = malloc(sizeof(char)
			* (ft_strlen(tmp_content) - env_len) + 1); // malloc NEWTOK for '=toto'
	if (token->next->next->content == NULL)
		return (NULL);
	while (tmp_content[++i + env_len])
		token->next->next->content[i] = tmp_content[i + env_len]; // Save =toto to NEWTOK
	token->next->next->content[i] = '\0';
	token->next->next->next = tmp_next;
	free(tmp_content);
	return (token);
}



static t_token	*clean_env(t_token *token) // First token type is DOLLAR ($)
{
	int		env_len;
	int		i;
	char	*tmp_content;

	env_len = env_len_size(token->next);
	i = -1;
	tmp_content = ft_strdup(token->next->content); // copy token->next->content (TEST=toto) to tmp_content
	free(token->next->content); // free token->next->content (TEST=toto)
	token->next->content = malloc(sizeof(char) * (env_len + 1)); // malloc token->next->content to content len
	if (token->next->content == NULL)
		return (NULL);
	while (++i < env_len) // Fill token->next->content whith env name (TEST)
		token->next->content[i] = tmp_content[i];
	token->next->content[i] = '\0';
	token = fill_new_token(token, tmp_content, env_len);
	if (token == NULL)
		return (NULL);
	return (token);
}

// static t_token	*split_env_token(t_token *token)
// {
// 	int		i;
// 	char	**split_content;

// 	i = 0;
// 	split_content = ft_split(token->content, ' ');
// 	free(token->content);
// 	token->content = ft_strdup(split_content[0]);
// 	token->type = WORD;
// 	i = 1;
// 	while (split_content[i])
// 	{
// 		token->next = add_token();
// 		token = token->next;
// 		token->content = ft_strdup(" ");
// 		token->type = WHITE_SPACE;
// 		token->next = add_token();
// 		token = token->next;
// 		token->content = ft_strdup(split_content[i++]);
// 		token->type = WORD;
// 	}
// 	i = 0;
// 	while (split_content[i])
// 	{
// 		free(split_content[i]);
// 		i++;
// 	}
// 	free(split_content);
// 	return (token);
// }

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
		// token = split_env_token(token);
	}
	else
	{
		token->content = NULL;
		token->type = 0;
		free(token->next->content);
		free(token->next);
	}
	token->next = tmp;
	return (token);
}

void	dollar_format(t_infos *infos, t_token *token)
{
	format_dollar_in_quote(token);
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
