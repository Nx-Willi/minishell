/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_for_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:19:14 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/25 15:29:37 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	char_env_len_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (ft_isalpha(str[i]) != 0
			|| ft_isalnum(str[i]) != 0 || str[i] == '_'))
		i++;
	return (i);
}

static char	*jump_to_first_dollar(char *str, char *return_char)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	return_char = malloc(sizeof(char) * (i + 1));
	if (!return_char)
		return (0);
	ft_strlcpy(return_char, str, i + 1);
	i = 1;
	return (return_char);
}

static char	*get_char_exit_status(char *return_char, char **str_split, int i)
{
	char	*exit_char;

	exit_char = ft_itoa(g_exit_status);
	return_char = _strjoin(return_char, exit_char);
	return_char = _strjoin(return_char, &str_split[i][1]);
	free(exit_char);
	return (return_char);
}

static char	*get_char_env(t_infos *infos, char **str_split,
		char *return_char, int i)
{
	char	*clean_env;
	char	*env;

	clean_env = malloc(sizeof(char) * char_env_len_size(str_split[i]) + 1);
	if (!clean_env)
		return (NULL);
	ft_strlcpy(clean_env, str_split[i], (char_env_len_size(str_split[i]) + 1));
	env = get_env_var_value(infos, clean_env);
	if (env == NULL)
		return_char = _strjoin(return_char, "");
	else
		return_char = _strjoin(return_char, env);
	return_char = _strjoin(return_char,
			&str_split[i][char_env_len_size(str_split[i])]);
	free(clean_env);
	return (return_char);
}

char	*get_env_for_heredoc(t_infos *infos, char *str)
{
	int		i;
	char	*return_char;
	char	**str_split;

	str_split = ft_split(str, '$');
	i = 0;
	return_char = NULL;
	if (str[0] != '$')
		return_char = jump_to_first_dollar(&str[i++], return_char);
	while (str_split[i])
	{
		if (str_split[i][0] == '?')
			return_char = get_char_exit_status(return_char, str_split, i);
		else
			return_char = get_char_env(infos, str_split, return_char, i);
		i++;
	}
	i = 0;
	while (str_split[i])
		free(str_split[i++]);
	free(str_split);
	return (return_char);
}
