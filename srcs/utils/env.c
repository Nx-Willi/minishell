/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 17:38:35 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_var(char *var, int from_env)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->from_env = from_env;
	if (from_env == TRUE)
		new->variable = var;
	else
	{
		new->variable = malloc(sizeof(char) * (ft_strlen(var) + 1));
		if (new->variable == NULL)
			return (NULL);
		ft_strlcpy(new->variable, var, ft_strlen(var) + 1);
	}
	new->next = NULL;
	return (new);
}

void	add_env_var(t_infos *infos, char *var, int from_env)
{
	t_env	*tmp;

	if (infos->env == NULL)
	{
		infos->env = new_env_var(var, from_env);
		return ;
	}
	tmp = infos->env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env_var(var, from_env);
}

/* Can segfault because isn't protected
if (infos->env != NULL)
	return ;
*/
void	remove_env_var(t_infos *infos, char *var)
{
	t_env	*tmp;
	t_env	*next;

	tmp = infos->env;
	if (varcmp(tmp->variable, var) == TRUE)
	{
		next = tmp->next;
		if (tmp->from_env == FALSE)
			free(tmp->variable);
		free(tmp);
		infos->env = next;
	}
	while (tmp->next != NULL)
	{
		next = tmp->next;
		if (varcmp(next->variable, var) == TRUE)
		{
			tmp->next = next->next;
			if (next->from_env == FALSE)
				free(next->variable);
			free(next);
			break ;
		}
		tmp = tmp->next;
	}
}
