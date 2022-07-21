/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:26:07 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 12:58:21 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	is_valid_var(t_cmd *cmd, char *var)
{
	int	i;

	if (ft_strchr(var, '=') != NULL)
	{
		puterror(cmd, var, "bad variable name");
		g_exit_status = FAILURE;
		return (FALSE);
	}
	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			puterror(cmd, var, "bad variable name");
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
		if (is_valid_var(cmd, cmd->argv[i]) == FALSE)
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
