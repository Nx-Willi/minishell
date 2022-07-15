/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:57:41 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 13:25:07 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			ft_putstr_fd(SH_NAME": export: bad variable name\n", 2);
			return (FALSE);
		}
		i++;
	}
	if (i == 0)
	{
		ft_putstr_fd(SH_NAME": export: bad variable name\n", 2);
		return (FALSE);
	}
	if (ft_strchr(var, '=') == NULL)
		return (FALSE);
	return (TRUE);
}

void	builtin_export(t_cmd *cmd)
{
	int	i;
	int	new_var;

	new_var = FALSE;
	i = 0;
	while (cmd->argv[++i] != NULL)
	{
		if (is_valid_identifier(cmd->argv[i]) == TRUE)
		{
			if (new_var == FALSE)
				new_var = TRUE;
			add_env_var(cmd->infos, cmd->argv[i], FALSE);
		}
		else
			g_exit_status = FAILURE;
	}
	if (new_var == TRUE)
	{
		cpy_env_to_char(cmd->infos);
		g_exit_status = SUCCESS;
	}
}
