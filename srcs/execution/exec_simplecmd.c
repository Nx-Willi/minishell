/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:49:58 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/23 17:14:04 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	redir_builtin(t_cmd *cmd)
{
	do_redirections(cmd);
	if (cmd->fd_in != -1)
		exec_builtin(cmd);
	clean_redirections(cmd);
}

void	exec_simple(t_cmd *cmd)
{
	int	pid;
	int	wstatus;

	wstatus = -1;
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		do_redirections(cmd);
		exec_cmd(cmd);
	}
	clean_redirections(cmd);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		g_exit_status = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			g_exit_status = INTERRUPT + WSTOPSIG(wstatus);
	}
}
