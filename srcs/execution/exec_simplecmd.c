/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:49:58 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 13:05:57 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	do_redirection(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		cmd->fdin_tmp = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
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
	int	wstatus;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		do_redirection(cmd);
		exec_cmd(cmd);
	}
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fdin_tmp, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fdout_tmp, STDOUT_FILENO);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		g_exit_status = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			g_exit_status = INTERRUPT + WSTOPSIG(wstatus);
	}
}
