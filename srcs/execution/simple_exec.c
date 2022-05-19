/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/19 18:49:52 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(char *command)
{
	pid_t	child_pid;
	pid_t	tmp_pid;
	int		child_status;
	char	*argv[] = { command, NULL };
	char	*envp[] = { NULL };

	tmp_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(command, argv, envp);
		printf("%s: command not found\n", command);
		exit(0);
	}
	else
	{
		while (tmp_pid != child_pid)
			tmp_pid = wait(&child_status);
		return ;
	}
}
