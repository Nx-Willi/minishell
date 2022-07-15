/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:26:07 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 13:26:29 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	is_valid_var(char *var)
{
	int	i;

	if (ft_strchr(var, '=') != NULL)
	{
		ft_putstr_fd(SH_NAME": unset: bad variable name\n", 2);
		g_exit_status = FAILURE;
		return (FALSE);
	}
	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			ft_putstr_fd(SH_NAME": unset: bad variable name\n", 2);
			g_exit_status = FAILURE;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static void	cpy_env(t_cmd *cmd, int rem_var)
{
	if (rem_var == TRUE)
	{
		g_exit_status = SUCCESS;
		cpy_env_to_char(cmd->infos);
	}
	else
		g_exit_status = FAILURE;
}

void	builtin_unset(t_cmd *cmd)
{
	int	i;
	int	rem_var;

	rem_var = FALSE;
	i = 1;
	if (cmd->argv[i] == NULL)
		return ;
	while (cmd->argv[i] != NULL)
	{
		if (is_valid_var(cmd->argv[i]) == FALSE)
		{
			i++;
			continue ;
		}
		if (is_var_in_env(cmd->infos->env, cmd->argv[i]))
		{
			rem_var = TRUE;
			remove_env_var(cmd->infos, cmd->argv[i]);
		}
		i++;
	}
	cpy_env(cmd, rem_var);
}
