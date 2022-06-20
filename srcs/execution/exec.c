/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/20 14:33:50 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipes(t_infos *infos)
{
	int		pid;
	int		fd[2];
	t_cmd	*cmds;

	cmds = infos->cmd;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(cmds->cmd_path, cmds->argv, cmds->infos->envp);
		printf("child\n");
		return ;
	}
	else
	{
		int	status;
		waitpid(-1, &status, 0);
		printf("toto\n");
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(cmds->next->cmd_path, cmds->next->argv, cmds->infos->envp);
		printf("parent\n");
		return ;
	}
}

void	exec_commands(t_infos *infos)
{
	t_cmd	*cmds;

	cmds = infos->cmd;
	if (cmds->next == NULL)
	{
		if (!is_builtin(cmds->argv[0]))
			exec_simple(infos, cmds);
		else
			exec_builtin(infos, cmds);
	}
	else
	{
		exec_pipes(infos);
		/*while (cmds != NULL)
		{
			if (!is_builtin(cmds->argv[0]))
				exec_simple(infos, cmds);
			else
				exec_builtin(infos, cmds);
			ft_putstr("\n\n");
			cmds = cmds->next;
		}*/
	}
}