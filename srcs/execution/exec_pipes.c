/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 12:43:59 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	do_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		cmd->fdin_tmp = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		cmd->fdout_tmp = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

static void	clean_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fdin_tmp, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fdout_tmp, STDOUT_FILENO);
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
		if (cmd->prev != NULL)
			dup2(pfds[cmd->prev->id][0], STDIN_FILENO);
		if (cmd->next != NULL)
			dup2(pfds[cmd->id][1], STDOUT_FILENO);
		do_redirections(cmd);
		close_pipes(NULL, pfds, cmd->infos->npipes, 0);
		if (is_builtin(cmd->argv[0]))
		{
			exec_builtin(cmd);
			exit(g_exit_status);
		}
		exec_cmd(cmd);
	}
	else
		clean_redirections(cmd);
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
		if (exec_child(cmd, pids, pfds) == FALSE)
			break ;
		cmd = cmd->next;
	}
	close_pipes(NULL, pfds, inf->npipes, inf->npipes);
	retwait_pids(inf, pids);
}
