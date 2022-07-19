/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:10:52 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/18 15:01:15 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	builtin_env(t_infos *infos)
{
	t_env	*tmp;

	if (infos->env == NULL)
	{
		ft_putstr_fd(SH_NAME": env: Unable to find environment!\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	tmp = infos->env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
	g_exit_status = SUCCESS;
}
