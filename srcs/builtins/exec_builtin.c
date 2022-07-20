/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:19:01 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/20 17:59:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *cmd)
{
	if (_strcmp(cmd->argv[0], "echo") == TRUE)
		builtin_echo(cmd);
	else if (_strcmp(cmd->argv[0], "cd") == TRUE)
		builtin_cd(cmd);
	else if (_strcmp(cmd->argv[0], "export") == TRUE)
		builtin_export(cmd);
	else if (_strcmp(cmd->argv[0], "unset") == TRUE)
		builtin_unset(cmd);
	else if (_strcmp(cmd->argv[0], "env") == TRUE)
		builtin_env(cmd->infos);
	else if (_strcmp(cmd->argv[0], "pwd") == TRUE)
		builtin_pwd(cmd->infos);
	else if (_strcmp(cmd->argv[0], "exit") == TRUE)
		builtin_exit(cmd);
}
