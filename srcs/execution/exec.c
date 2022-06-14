/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/14 13:38:13 by wdebotte         ###   ########.fr       */
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
		execve(cmds->next->cmd_path, cmds->next->argv, (char **)0);
	}
	else
	{
		char buffer[4096];

		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
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
