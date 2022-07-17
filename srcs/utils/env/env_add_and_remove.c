/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_and_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/18 00:22:50 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_var(char *var, int from_env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
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

static void	replace_env_var(t_env *env, char *var)
{
	while (env != NULL)
	{
		if (varcmp(env->variable, var) == TRUE)
		{
			if (env->from_env == FALSE)
				free(env->variable);
			else
				env->from_env = FALSE;
			env->variable = ft_substr(var, 0, ft_strlen(var) + 1);
			if (env->variable == NULL)
				printf("Error: malloc: replace_env_var\n");
			break ;
		}
		env = env->next;
	}
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
	if (is_var_in_env(infos->env, var) == FALSE)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env_var(var, from_env);
	}
	else
		replace_env_var(tmp, var);
}

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
