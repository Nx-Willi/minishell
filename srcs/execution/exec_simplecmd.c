/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:49:58 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/14 07:58:28 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirection(t_cmd *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
	{
		cmd->fdout_tmp = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

void	exec_simple(t_cmd *cmd)
{
	int	pid;
	int	status;

	do_redirection(cmd);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_in, STDIN_FILENO);
		exec_cmd(cmd);
	}
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fdout_tmp, STDOUT_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmd->infos->wstatus = WEXITSTATUS(status);
}
