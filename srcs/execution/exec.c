/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/21 11:25:48 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipes(t_infos *infos)
{
	int	*pfd;

	pfd = (int *)
}

/*void	exec_pipes(t_infos *infos)
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
		exec_pipes(infos);
}
