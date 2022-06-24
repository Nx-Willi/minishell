/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:37:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/24 15:26:25 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_param(char *param)
{
	int	i;

	i = 1;
	while (param[i] != '\0')
		if (param[i++] != 'n')
			return (FALSE);
	return (TRUE);
}

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	newline = TRUE;
	i = 0;
	while (cmd->argv[++i] != NULL)
	{
		if (cmd->argv[i][0] == '-')
		{
			if (check_param(cmd->argv[i]) == TRUE)
				newline = FALSE;
			else
				break ;
		}
		else
			break ;
	}
	while (cmd->argv[i] != NULL)
	{
		ft_putstr(cmd->argv[i]);
		if (cmd->argv[++i] != NULL)
			ft_putchar(' ');
	}
	if (newline == TRUE)
		ft_putchar('\n');
}
