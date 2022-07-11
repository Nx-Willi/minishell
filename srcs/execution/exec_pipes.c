/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/11 17:21:38 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirection(t_cmd *cmd, int **pfds)
{
	if (cmd->prev != NULL)
		dup2(pfds[cmd->prev->id][0], STDIN_FILENO);
	if (cmd->next != NULL)
		dup2(pfds[cmd->id][1], STDOUT_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

static int	exec_child(t_cmd *cmd, int *pids, int **pfds)
{
	pids[cmd->id] = fork();
	if (pids[cmd->id] < 0)
	{
		close_pipes(SH_NAME": exec_pipes: fork error\n", pfds,
			cmd->infos->npipes, cmd->infos->npipes);
		return (FALSE);
	}
	else if (pids[cmd->id] == 0)
	{
		do_redirection(cmd, pfds);
		close_pipes(NULL, pfds, cmd->infos->npipes, 0);
		if (is_builtin(cmd->argv[0]))
		{
			exec_builtin(cmd);
			exit(EXIT_SUCCESS);
		}
		exec_cmd(cmd);
	}
	else
		dup2(cmd->fd_tmp, STDOUT_FILENO);
	return (TRUE);
}

void	exec_pipes(t_infos *inf)
{
	int		*pids;
	int		**pfds;
	t_cmd	*cmd;

	pfds = init_pipefds(inf->npipes);
	if (pfds == NULL)
		return ;
	pids = (int *)malloc(sizeof(int) * (inf->npipes + 1));
	if (pids == NULL)
	{
		close_pipes(SH_NAME": malloc error\n", pfds, inf->npipes, inf->npipes);
		return ;
	}
	cmd = inf->cmd;
	while (cmd != NULL)
	{
		if (cmd->fd_out != STDOUT_FILENO)
			cmd->fd_tmp = dup(STDOUT_FILENO);
		if (exec_child(cmd, pids, pfds) == FALSE)
			break ;
		cmd = cmd->next;
	}
	close_pipes(NULL, pfds, inf->npipes, inf->npipes);
	retwait_pids(inf, pids);
}
