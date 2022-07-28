/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:57:14 by xle-baux          #+#    #+#             */
/*   Updated: 2022/07/28 16:09:11 by wdebotte         ###   ########.fr       */
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

static t_env	*cpy_var(t_env *env)
{
	t_env	*buffer;

	buffer = (t_env *)malloc(sizeof(t_env));
	if (buffer == NULL)
		return (NULL);
	buffer->from_env = FALSE;
	buffer->variable = ft_strdup(env->variable);
	if (buffer->variable == NULL)
	{
		free(buffer);
		return (NULL);
	}
	buffer->next = NULL;
	return (buffer);
}

static t_env	*cpy_env(t_env *env)
{
	t_env	*tmp;
	t_env	*buffer;
	t_env	*buffer_start;

	tmp = env;
	buffer = cpy_var(tmp);
	buffer_start = buffer;
	while (tmp->next != NULL)
	{
		buffer->next = cpy_var(tmp->next);
		buffer = buffer->next;
		tmp = tmp->next;
	}
	return (buffer_start);
}

t_env	*sort_env(t_env *env)
{
	int		sorted;
	t_env	*start_env;
	t_env	*tmp;

	if (env == NULL)
		return (NULL);
	sorted = FALSE;
	tmp = cpy_env(env);
	start_env = tmp;
	while (sorted == FALSE)
	{
		sorted = TRUE;
		while (tmp->next)
		{
			sorted = check_if_swap(tmp, sorted);
			tmp = tmp->next;
		}
		tmp = start_env;
	}
	return (start_env);
}
