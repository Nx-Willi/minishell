/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:26:07 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 16:00:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var(char *var)
{
	int	i;

	if (ft_strchr(var, '=') != NULL)
	{
		ft_putstr_fd(SH_NAME": unset: bad variable name\n", 2);
		return (FALSE);
	}
	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			ft_putstr_fd(SH_NAME": unset: bad variable name\n", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	builtin_unset(t_infos *infos)
{
	int	i;
	int	rem_var;

	rem_var = FALSE;
	i = 1;
	if (infos->argv[i] == NULL)
		return ;
	while (infos->argv[i] != NULL)
	{
		if (is_valid_var(infos->argv[i]) == FALSE)
		{
			i++;
			continue ;
		}
		if (is_var_in_env(infos->env, infos->argv[i]))
		{
			rem_var = TRUE;
			remove_env_var(infos, infos->argv[i]);
		}
		i++;
	}
	if (rem_var == TRUE)
		cpy_env_to_char(infos);
}
