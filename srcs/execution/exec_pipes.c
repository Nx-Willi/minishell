/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/24 15:38:48 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
		close_pipes(NULL, pfds, cmd->infos->npipes, cmd->infos->npipes);
		if (is_builtin(cmd->argv[0]))
		{
			exec_builtin(cmd);
			free(pids);
			exit_program(cmd->infos, g_exit_status);
		}
		exec_cmd(cmd, pids);
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
