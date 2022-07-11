/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:49:58 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/11 14:30:17 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_cmd *cmd)
{
	int	pid;
	int	status;

	if (cmd->fd_out != STDOUT_FILENO)
		cmd->fd_tmp = dup(STDOUT_FILENO);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		if (cmd->fd_out != STDOUT_FILENO)
		{
			close(STDOUT_FILENO);
			dup2(cmd->fd_out, STDOUT_FILENO);
		}
		exec_cmd(cmd);
	}
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_tmp, STDOUT_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmd->infos->wstatus = WEXITSTATUS(status);
}
