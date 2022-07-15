/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 12:06:43 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_commands(t_infos *infos)
{
	if (infos->npipes == 0)
	{
		if (is_builtin(infos->cmd->argv[0]))
			exec_builtin(infos->cmd);
		else
			exec_simple(infos->cmd);
	}
	else
		exec_pipes(infos);
}
