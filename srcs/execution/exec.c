/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/27 16:03:37 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_simple(t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		exec_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmd->infos->wstatus = WEXITSTATUS(status);
}

void	exec_commands(t_infos *infos)
{
	if (infos->npipes == 0)
	{
		if (is_builtin(infos->cmd->argv[0]))
		{
			exec_builtin(infos->cmd);
			infos->wstatus = 0;
		}
		else
			exec_simple(infos->cmd);
	}
	else
		exec_pipes(infos);
}
