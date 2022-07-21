/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:49:59 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 15:55:03 by wdebotte         ###   ########.fr       */
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

	tmp = cmd;
	while (tmp)
	{
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

void	exit_program(int exit_code)
{
	rl_clear_history();
	exit(exit_code);
}
