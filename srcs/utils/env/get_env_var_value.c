/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:19:32 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 16:19:37 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var_value(t_infos *infos, char *var)
{
	int		i;
	char	*env_var;
	t_env	*tmp;

	env_var = NULL;
	if (is_var_in_env(infos->env, var) == FALSE)
		return (NULL);
	tmp = infos->env;
	while (tmp != NULL)
	{
		if (varcmp(tmp->variable, var) == TRUE)
		{
			env_var = tmp->variable;
			break ;
		}
		tmp = tmp->next;
	}
	if (env_var == NULL)
		return (NULL);
	i = 0;
	while (env_var[i] != '\0' && env_var[i] != '=')
		i++;
	if (env_var[++i] == '\0')
		return (NULL);
	return (env_var + i);
}
