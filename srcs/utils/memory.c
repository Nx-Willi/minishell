/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:49:59 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/23 18:34:01 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	free_char_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->from_env == FALSE)
			free(tmp->variable);
		tmp = tmp->next;
		free(env);
		env = tmp;
	}
	free(env);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	if (cmd == NULL)
		return ;
	tmp = cmd;
	while (tmp)
	{
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (_strcmp(cmd->cmd_path, cmd->argv[0]) == FALSE)
			free(cmd->cmd_path);
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
		tmp = tmp->next;
		free(cmd);
		cmd = tmp;
	}
	free(cmd);
}

void	exit_program(t_infos *infos, int exit_code)
{
	free(infos->envp);
	free_env(infos->env);
	free(infos->prompt);
	if (infos->cmd != NULL)
		free_cmd(infos->cmd);
	rl_clear_history();
	exit(exit_code);
}
