/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:57:14 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/25 17:05:51 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(t_env *env)
{
	int		tmp_from_env;
	char	*tmp_variable;

	tmp_from_env = env->from_env;
	tmp_variable = env->variable;
	env->from_env = env->next->from_env;
	env->variable = env->next->variable;
	env->next->from_env = tmp_from_env;
	env->next->variable = tmp_variable;
}

static int	check_if_swap(t_env *env, int sorted)
{
	int	i;

	i = 0;
	while (env->variable[i] != '\0' && env->next->variable[i] != '\0')
	{
		if (env->variable[i] > env->next->variable[i])
		{
			swap(env);
			sorted = FALSE;
			break ;
		}
		else if (env->variable[i] < env->next->variable[i])
			break ;
		else
			i++;
	}
	return (sorted);
}

t_env	*sort_env(t_env *env)
{
	int		sorted;
	t_env	*start_env;

	sorted = FALSE;
	start_env = env;
	while (sorted == FALSE)
	{
		sorted = TRUE;
		while (env->next)
		{
			sorted = check_if_swap(env, sorted);
			env = env->next;
		}
		env = start_env;
	}
	return (start_env);
}
