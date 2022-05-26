/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:10:52 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 17:06:46 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_infos *infos)
{
	t_env	*tmp;

	if (infos->env == NULL)
		return ;
	tmp = infos->env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
}
