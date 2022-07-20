/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:44:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/20 16:53:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	printerror(t_cmd *cmd, char *error)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}

void	exec_cmd(t_cmd *cmd)
{
	if (access(cmd->cmd_path, F_OK) == -1)
	{
		printerror(cmd, "command not found\n");
		exit(DOESNT_EXIST);
	}
	else if (access(cmd->cmd_path, X_OK) == -1)
	{
		printerror(cmd, "Permission denied\n");
		exit(BAD_PERMIT);
	}
	if (cmd->fd_in != -1)
		execve(cmd->cmd_path, cmd->argv, cmd->infos->envp);
	exit(FAILURE);
}
