/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:44:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 15:30:07 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	exec_commands(t_infos *infos)
{
	if (infos->npipes == 0)
	{
		if (is_builtin(infos->cmd->argv[0]))
			redir_builtin(infos->cmd);
		else
			exec_simple(infos->cmd);
	}
	else
		exec_pipes(infos);
}

void	exec_cmd(t_cmd *cmd)
{
	if (access(cmd->cmd_path, F_OK) == -1)
	{
		puterror(cmd, NULL, "Command not found");
		exit(DOESNT_EXIST);
	}
	else if (access(cmd->cmd_path, X_OK) == -1)
	{
		puterror(cmd, NULL, "Permission denied");
		exit(BAD_PERMIT);
	}
	if (cmd->fd_in != -1)
		execve(cmd->cmd_path, cmd->argv, cmd->infos->envp);
	exit(FAILURE);
}
