/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:06:24 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 09:57:45 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char *line)
{
	int	i;
	int	argc;

	i = 0;
	argc = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && is_whitespace(line[i]))
			i++;
		if (line[i] != '\0' && !is_whitespace(line[i]))
		{
			if (line[i] == '\'')
				while (line[++i] != '\0' && line[i] != '\'')
					continue ;
			else if (line[i] == '\"')
				while (line[++i] != '\0' && line[i] != '\"')
					continue ;
			i++;
			argc++;
		}
		while (line[i] != '\0' && !is_whitespace(line[i]))
			i++;
	}
	return (argc);
}

static int	size_to_next_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\'')
			i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\"')
			i++;
	}
	else
		while (str[i] != '\0' && !is_whitespace(str[i]))
			i++;
	return (i);
}

static char	*add_to_tab(char *str)
{
	int		i;
	int		n;
	char	*buffer;

	buffer = malloc(sizeof(char) * (size_to_next_char(str) + 1));
	if (buffer == NULL)
		return (buffer);
	i = 0;
	n = 0;
	if (str[i] == '\'')
		while (str[++i] != '\0' && str[i] != '\'')
			buffer[n++] = str[i];
	else if (str[i] == '\"')
		while (str[++i] != '\0' && str[i] != '\"')
			buffer[n++] = str[i];
	else
		while (str[i] != '\0' && !is_whitespace(str[i]))
			buffer[n++] = str[i++];
	buffer[n] = '\0';
	return (buffer);
}

char	**get_command_args(char *line)
{
	int		i;
	int		n;
	char	**argv;

	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
	{
		argv = malloc(sizeof(char *) * (count_args(line) + 1));
		if (argv == NULL)
			return (NULL);
		i = 0;
		n = 0;
		while (line[i] != '\0')
		{
			while (line[i] != '\0' && is_whitespace(line[i]))
				i++;
			if (n == 0)
				argv[n++] = get_command_path(line + i);
			else
				argv[n++] = add_to_tab(line + i);
			i += size_to_next_char(line + i) + 1;
		}
		argv[n] = NULL;
	}
	else
		argv = ft_split(line, ' ');
	return (argv);
}
