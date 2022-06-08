/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:49:59 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/03 14:21:18 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

//Censer etre free mais ca marche sans free
//free(infos->envp);
//free_env(infos->env);
int	exit_program(t_infos *infos, int exit_code, int started)
{
	if (started == TRUE)
	{
		free(infos->line);
		free(infos->cmd_name);
		free(infos->cmd_path);
		free_char_tab(infos->argv);
	}
	rl_clear_history();
	exit(exit_code);
	return (exit_code);
}
