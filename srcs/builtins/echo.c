/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:39:10 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 12:46:34 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_infos *infos)
{
	int	i;
	int	newline;

	if (infos->argv[1] != NULL && _strcmp(infos->argv[1], "-n") == TRUE)
	{
		i = 2;
		newline = FALSE;
	}
	else
	{
		i = 1;
		newline = TRUE;
	}
	while (infos->argv[i] != NULL)
	{
		ft_putstr(infos->argv[i++]);
		/*if (next arg refers to "" or '')
			continue ;*/
		ft_putchar(' ');
	}
	if (newline == TRUE)
		ft_putchar('\n');
}
