/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:19:01 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/25 16:58:28 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	value(char *cmd, int value)
{
	free(cmd);
	return (value);
}

int	is_builtin(char *line)
{
	char	*cmd;

	cmd = get_cmd_name(line);
	if (ft_strncmp(line, "echo", ft_strlen(cmd)) == 0)
		return (free(cmd), TRUE);
	else if (ft_strncmp(line, "cd", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	else if (ft_strncmp(line, "pwd", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	else if (ft_strncmp(line, "export", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	else if (ft_strncmp(line, "unset", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	else if (ft_strncmp(line, "env", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	else if (ft_strncmp(line, "exit", ft_strlen(cmd)) == 0)
		return (value(cmd, TRUE));
	return (value(cmd, FALSE));
}

void	exec_builtin(t_infos *infos)
{
	char	**argv;
	char	*cmd;

	//Do argv in struct for all function
	argv = get_command_args(infos->line);
	cmd = argv[0];
	/*if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		builtin_echo(argv);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		builtin_cd(argv);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		builtin_pwd(argv);
	else */if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		builtin_export(infos, argv);
	/*else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		builtin_unset(argv);
	else */if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		builtin_env(infos);/*
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		builtin_exit(argv);*/
}
