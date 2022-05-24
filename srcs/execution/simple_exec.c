/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/24 17:40:02 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_infos *infos)
{
	pid_t	child_pid;
	pid_t	tmp_pid;
	char	*cmd;
	char	**argv;

	cmd = get_command_path(infos->line);
	argv = get_command_args(infos->line);
	tmp_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd, argv, (void *)0);
		printf("%s: command not found\n", cmd);
		free(cmd);
		free_char_tab(argv);
		exit(0);
	}
	else
	{
		while (tmp_pid != child_pid)
			tmp_pid = wait(NULL);
		free(cmd);
		free_char_tab(argv);
		return ;
	}
}
