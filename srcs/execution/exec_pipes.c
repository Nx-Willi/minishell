/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/11 11:13:24 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirect(t_cmd *cmd, int **pfds)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->prev != NULL)
		dup2(pfds[cmd->prev->id][0], STDIN_FILENO);
	if (cmd->next != NULL)
		dup2(pfds[cmd->id][1], STDOUT_FILENO);
}

static void	read_and_write_in_fd(t_cmd *cmd)
{
	char	buffer[SSIZE_MAX];

	if (cmd->fd_out != STDOUT_FILENO)
	{
		read(STDOUT_FILENO, buffer, sizeof(buffer));
		printf("%s\n", buffer);
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
	else if (pids[cmd->id] > 0)
		return (TRUE);
	do_redirect(cmd, pfds);
	close_pipes(NULL, pfds, cmd->infos->npipes, 0);
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd);
		read_and_write_in_fd(cmd);
		exit(EXIT_SUCCESS);
	}
	exec_cmd(cmd);
	read_and_write_in_fd(cmd);
	exit(EXIT_FAILURE);
}

void	exec_pipes(t_infos *inf)
{
	int		*pids;
	int		**pfds;
	t_cmd	*cmds;

	pfds = init_pipefds(inf->npipes);
	if (pfds == NULL)
		return ;
	pids = (int *)malloc(sizeof(int) * (inf->npipes + 1));
	if (pids == NULL)
	{
		close_pipes(SH_NAME": malloc error\n", pfds, inf->npipes, inf->npipes);
		return ;
	}
	cmds = inf->cmd;
	while (cmds != NULL)
	{
		if (exec_child(cmds, pids, pfds) == FALSE)
			break ;
		cmds = cmds->next;
	}
	close_pipes(NULL, pfds, inf->npipes, inf->npipes);
	retwait_pids(inf, pids);
}
