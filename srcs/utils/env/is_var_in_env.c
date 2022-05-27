/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:00:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 16:17:02 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_in_env(t_env *env, char *var)
{
	t_env	*tmp;

	if (var == NULL)
		return (FALSE);
	tmp = env;
	while (tmp != NULL)
	{
		if (varcmp(tmp->variable, var) == TRUE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}
