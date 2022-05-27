/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:32:46 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 18:05:06 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_env_to_lst(t_infos *infos, char **envp)
{
	int	i;

	if (*envp == NULL)
		return ;
	i = 0;
	infos->env = new_env_var(envp[i++], TRUE);
	while (envp[i] != NULL)
		add_env_var(infos, envp[i++], TRUE);
}

static int	get_env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	cpy_env_to_char(t_infos *infos)
{
	int		i;
	int		env_size;
	t_env	*tmp;

	if (infos->env == NULL)
		return ;
	if (infos->envp != NULL)
		free(infos->envp);
	env_size = get_env_size(infos->env);
	infos->envp = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (infos->envp == NULL)
		return ;
	i = 0;
	tmp = infos->env;
	while (tmp != NULL)
	{
		infos->envp[i++] = tmp->variable;
		tmp = tmp->next;
	}
	infos->envp[i] = NULL;
}
