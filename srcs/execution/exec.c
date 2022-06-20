/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/20 16:06:16 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipes(t_infos *infos)
{
	int		pfd[2];
	int		pids[2];
	t_cmd	*cmds;

	cmds = infos->cmd;
	if (pipe(pfd) < 0)
		return ;
	pids[0] = fork();
	if (pids[0] < 0)
		return ;
	if (pids[0] == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execve(cmds->cmd_path, cmds->argv, infos->envp);
		printf("child1: command not found\n");
		exit(EXIT_FAILURE);
	}
	pids[1] = fork();
	if (pids[1] < 0)
		return ;
	if (pids[1] == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		execve(cmds->next->cmd_path, cmds->next->argv, infos->envp);
		printf("child2: command not found\n");
		exit(EXIT_FAILURE);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

/*void	exec_pipes(t_infos *infos)
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
}*/

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
