/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/23 13:28:41 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_infos *infos, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(SH_NAME": exec_simple: fork error\n", 2);
		return ;
	}
	else if (pid == 0)
	{
		execve(cmd->cmd_path, cmd->argv, infos->envp);
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
