/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/25 11:40:59 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_var(char *variable)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->variable = variable;
	new->next = NULL;
	return (new);
}

void	add_env_var(t_env *env, char *variable)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env_var(variable);
}

void	cpy_env(t_env **env, char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0; 
	*env = new_env_var(envp[i++]);
	while (envp[i] != NULL)
		add_env_var(*env, envp[i++]);
}
