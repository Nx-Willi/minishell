/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:39:26 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/18 17:15:43 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	is_arg_correct(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	builtin_exit(t_cmd *cmd)
{
	int	exit_status;

	if (cmd->next != NULL || cmd->prev != NULL)
		exit_status = 1;
	else
		exit_status = 0;
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (cmd->argv[1] != NULL && !is_arg_correct(cmd->argv[1]))
	{
		ft_putstr_fd(SH_NAME": exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		//bash exit the program with printing exit => exit_program(status)
		//have to check exit value
	}
	if (cmd->argv[1] != NULL && cmd->argv[2] != NULL)
	{
		ft_putstr_fd(SH_NAME": exit: too many arguments\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	else
		//Only one argument, get atoi of him and goto exit_program(status)
}
