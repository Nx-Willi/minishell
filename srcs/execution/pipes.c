/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/27 16:04:31 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(char *error, int **pfds, int idx_pipes, int idx_tab)
{
	int	i;

	i = -1;
	while (++i < idx_pipes)
	{
		if (close(pfds[i][0]) < 0)
			ft_putstr_fd(SH_NAME": close_pipes: close error\n", 2);
		if (close(pfds[i][1]) < 0)
			ft_putstr_fd(SH_NAME": close_pipes: close error\n", 2);
	}
	if (idx_tab > 0)
	{
		i = 0;
		while (i < idx_tab)
			free(pfds[i++]);
		free(pfds);
	}
	if (error != NULL)
		ft_putstr_fd(error, 2);
}

static int	**init_pipefds(int npipes)
{
	int	i;
	int	**pfds;

	pfds = (int **)malloc(sizeof(int *) * npipes);
	if (pfds == NULL)
	{
		ft_putstr_fd(SH_NAME": pipefds: malloc error\n", 2);
		return (NULL);
	}
	i = -1;
	while (++i < npipes)
	{
		pfds[i] = (int *)malloc(sizeof(int) * 2);
		if (pfds[i] == NULL)
		{
			close_pipes(SH_NAME": pipefds: malloc error\n", pfds, i - 1, i - 1);
			return (NULL);
		}
		if (pipe(pfds[i]) < 0)
		{
			close_pipes(SH_NAME": pipefds: pipe error\n", pfds, i - 1, i);
			return (NULL);
		}
	}
	return (pfds);
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
	if (cmd->prev != NULL)
		dup2(pfds[cmd->prev->id][0], STDIN_FILENO);
	if (cmd->next != NULL)
		dup2(pfds[cmd->id][1], STDOUT_FILENO);
	close_pipes(NULL, pfds, cmd->infos->npipes, 0);
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd);
		exit(EXIT_SUCCESS);
	}
	exec_cmd(cmd);
	exit(EXIT_FAILURE);
}

static void	retwait_pids(t_infos *infos, int *pids)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < infos->npipes + 1)
		waitpid(pids[i], &wstatus, 0);
	if (WIFEXITED(wstatus))
		infos->wstatus = WEXITSTATUS(wstatus);
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
