/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:39:26 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 14:21:48 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static unsigned long long	atoull(char *str)
{
	int					is_negativ;
	unsigned long long	number;

	number = 0;
	is_negativ = 1;
	while (*str && is_whitespace(*str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		if (*(str++) == '-')
			is_negativ = -is_negativ;
	while (*str && (*str >= '0' && *str <= '9'))
		number = number * 10 + *(str++) - 48;
	return (number * is_negativ);
}

static int	is_arg_correct(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
		i++;
	}
	if (arg[0] == '-' && atoull(arg + 1) > ULLLIMIT + 1)
		return (FALSE);
	else if (arg[0] != '-' && atoull(arg) > ULLLIMIT)
		return (FALSE);
	return (TRUE);
}

static long long int	get_exit_status(t_cmd *cmd)
{
	if (cmd->argv[1] != NULL && !is_arg_correct(cmd->argv[1]))
	{
		puterror(cmd, cmd->argv[1], "numeric argument required");
		return (FAILURE + 1);
	}
	if (cmd->argv[1] != NULL && cmd->argv[2] != NULL)
	{
		puterror(cmd, NULL, "too many arguments");
		return (FAILURE);
	}
	return (atoull(cmd->argv[1]) & 0377);
}

void	builtin_exit(t_cmd *cmd)
{
	int	exit_status;

	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (cmd->argv[1] != NULL)
		exit_status = get_exit_status(cmd);
	else
		exit_status = SUCCESS;
	if (exit_status != FAILURE)
	{
		rl_clear_history();
		exit(exit_status);
	}
	else
		g_exit_status = FAILURE;
}
