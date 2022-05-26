/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:26:07 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 16:50:11 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_in_env(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (varcmp(tmp->variable, var) == TRUE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

static int	is_valid_var(char *var)
{
	int	i;

	if (ft_strchr(var, '=') != NULL)
	{
		printf("unset: %s: not a valid identifier\n", var);
		return (FALSE);
	}
	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			printf("unset: %s: not a valid identifier\n", var);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	builtin_unset(t_infos *infos)
{
	int	i;

	i = 1;
	if (infos->argv[i] == NULL)
		return ;
	while (infos->argv[i] != NULL)
	{
		if (is_valid_var(infos->argv[i]) == FALSE)
		{
			i++;
			continue ;
		}
		if (is_var_in_env(infos->env, infos->argv[i]))
			remove_env_var(infos, infos->argv[i]);
		i++;
	}
	cpy_env_to_char(infos);
}
