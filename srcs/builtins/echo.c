/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:37:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/27 15:20:55 by wdebotte         ###   ########.fr       */
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

static int	is_dol_ques_mark(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] != '\0')
		{
			if (str[i] == '$' && str[i + 1] == '?')
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static void	put_arg(t_cmd *cmd, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] != '\0')
		{
			if (arg[i] == '$' && arg[i + 1] == '?')
			{
				ft_putnbr(cmd->infos->wstatus);
				i += 2;
			}
		}
		ft_putchar(arg[i++]);
	}
}

static void	print_args(t_cmd *cmd, int newline, int idx)
{
	while (cmd->argv[idx] != NULL)
	{
		if (is_dol_ques_mark(cmd->argv[idx]) == TRUE)
			put_arg(cmd, cmd->argv[idx]);
		else
			ft_putstr(cmd->argv[idx]);
		if (cmd->argv[++idx] != NULL)
			ft_putchar(' ');
	}
	if (newline == TRUE)
		ft_putchar('\n');
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
	print_args(cmd, newline, i);
}
