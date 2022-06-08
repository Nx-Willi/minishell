/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 16:50:56 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_infos *infos)
{
	pid_t	child_pid;
	pid_t	tmp_pid;

	tmp_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(infos->cmd_path, infos->argv, infos->envp);
		printf("%s: command not found\n", infos->cmd_path);
		exit(0);
	}
	else
	{
		while (tmp_pid != child_pid)
			tmp_pid = wait(NULL);
		return ;
	}
}
