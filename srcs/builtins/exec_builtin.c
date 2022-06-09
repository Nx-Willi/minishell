/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:19:01 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/09 18:31:03 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (_strcmp(cmd->argv[0], "echo") == TRUE)
		builtin_echo(infos);
*/

void	exec_builtin(t_infos *infos, t_cmd *cmd)
{
	if (_strcmp(cmd->argv[0], "cd") == TRUE)
		builtin_cd(infos, cmd);
	else if (_strcmp(cmd->argv[0], "export") == TRUE)
		builtin_export(infos, cmd);
	else if (_strcmp(cmd->argv[0], "unset") == TRUE)
		builtin_unset(infos, cmd);
	else if (_strcmp(cmd->argv[0], "env") == TRUE)
		builtin_env(infos);
	else if (_strcmp(cmd->argv[0], "pwd") == TRUE)
		builtin_pwd();
	else if (_strcmp(cmd->argv[0], "exit") == TRUE)
		exit_program(EXIT_SUCCESS);
}
