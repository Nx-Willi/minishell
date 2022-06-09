/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/09 12:31:43 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_infos *infos, t_cmd *cmd)
{
	pid_t	child_pid;
	pid_t	tmp_pid;

	tmp_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd->cmd_path, cmd->argv, infos->envp);
		printf("%s: command not found\n", cmd->cmd_path);
		exit(0);
	}
	else
	{
		while (tmp_pid != child_pid)
			tmp_pid = wait(NULL);
		return ;
	}
}
