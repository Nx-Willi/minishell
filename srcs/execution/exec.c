/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/22 18:15:20 by wdebotte         ###   ########.fr       */
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
	if (pfds == NULL
		&& ft_putstr_fd(SH_NAME": init_pipefds: malloc error\n", 2))
		return (NULL);
	i = -1;
	while (++i < npipes)
	{
		pfds[i] = (int *)malloc(sizeof(int) * 2);
		if (pfds[i] == NULL)
		{
			close_pipes(SH_NAME": init_pipefds: malloc error\n", pfds,
				i - 1, i - 1);
			return (NULL);
		}
		if (pipe(pfds[i]) < 0)
		{
			close_pipes(SH_NAME": init_pipefds: pipe error\n", pfds, i - 1, i);
			return (NULL);
		}
	}
	return (pfds);
}

static void	*exec_commands(t_cmd *cmds, int *pids, int **pfds)
{
	pids[cmds->id] = fork();
	if (pids[cmds->id] < 0)
	{
		close_pipes(SH_NAME": exec_pipes: fork error\n", pfds,
			infos->npipes, infos->npipes);
		return (NULL);
	}
	else if (pids[cmds->id] == 0)
	{
		if (cmds->prev != NULL)
			dup2(pfds[cmds->prev->id][0], STDIN_FILENO);
		if (cmds->next != NULL)
			dup2(pfds[cmds->id][1], STDOUT_FILENO);
		close_pipes(NULL, pfds, infos->npipes, 0);
		execve(cmds->cmd_path, cmds->argv, infos->envp);
		ft_putstr_fd(SH_NAME": ", 2);
		ft_putstr_fd(cmds->cmd_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	return ((int)TRUE);
}

static void	exec_pipes(t_infos *infos)
{
	int		i;
	int		*pids;
	int		**pfds;
	t_cmd	*cmds;

	pfds = init_pipefds(infos->npipes);
	if (pfds == NULL)
		return ;
	pids = (int *)malloc(sizeof(int) * (infos->npipes + 1));
	if (pids == NULL && close_pipes(SH_NAME": exec_pipes: malloc error\n", pfds,
			infos->npipes, infos->npipes))
		return ;
	cmds = infos->cmd;
	while (cmds != NULL)
	{
		if (exec_commands(cmds, pids, pfds) == NULL)
			break ;
		cmds = cmds->next;
	}
	close_pipes(NULL, pfds, infos->npipes, infos->npipes);
	i = -1;
	while (++i < infos->npipes + 1)
		waitpid(pids[i], NULL, 0);
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
		exec_pipes(infos);
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
