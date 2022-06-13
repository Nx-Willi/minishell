/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:51:31 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/13 17:34:03 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_commands(t_infos *infos)
{
	t_cmd	*cmds;

	cmds = infos->cmd;
	if (cmds->next == NULL)
	{
		if (!is_builtin(cmds->argv[0]))
			exec_simple(infos, cmds);
		else
			exec_builtin(infos, cmds);
	}
	else
	{
		while (cmds != NULL)
		{
			if (!is_builtin(cmds->argv[0]))
				exec_simple(infos, cmds);
			else
				exec_builtin(infos, cmds);
			ft_putstr("\n\n");
			cmds = cmds->next;
		}
	}
}
