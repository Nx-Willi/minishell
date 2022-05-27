/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:19:01 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 15:52:14 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_infos *infos)
{
	if (_strcmp(infos->cmd_name, "echo") == TRUE)
		builtin_echo(infos);
	else if (_strcmp(infos->cmd_name, "cd") == TRUE)
		builtin_cd(infos);
	/*else if (_strcmp(infos->cmd_name, "pwd") == TRUE)
		builtin_pwd(infos->argv);*/
	else if (_strcmp(infos->cmd_name, "export") == TRUE)
		builtin_export(infos);
	else if (_strcmp(infos->cmd_name, "unset") == TRUE)
		builtin_unset(infos);
	else if (_strcmp(infos->cmd_name, "env") == TRUE)
		builtin_env(infos);
	/*else if (_strcmp(infos->cmd_name, "exit") == TRUE)
		builtin_exit(infos->argv);*/
}
