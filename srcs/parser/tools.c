/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:36:04 by xle-baux          #+#    #+#             */
/*   Updated: 2022/06/25 17:59:29 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*missing(void)
{
	char	*s;

	s = malloc(sizeof(char));
	s[0] = '\0';
	return (s);
}

char	*_strjoin(char *s1, char *s2)
{
	int		i;
	char	*join;

	if (!s1)
		s1 = missing();
	if (!s2)
		s2 = missing();
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
}

int	count_commands(t_token *token)
{
	int	pipe;

	pipe = 0;
	while (token->next)
	{
		if (token->type == PIPE)
			pipe++;
		token = token->next;
	}
	return (pipe + 1);
}

void	add_id(t_cmd *cmd)
{
	int	id;

	id = 0;
	while (cmd)
	{
		cmd->id = id++;
		cmd = cmd->next;
	}
}

t_token	*ignore_white_space(t_token *token)
{
	while (token->type == WHITE_SPACE)
		token = token->next;
	return (token);
}
