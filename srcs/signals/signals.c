/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:34:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/28 13:15:48 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	get_signals(int in_exec)
{
	if (in_exec == FALSE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler_int);
	}
	else if (in_exec == TRUE)
	{
		signal(SIGQUIT, &handler_quit_exec);
		signal(SIGINT, &handler_int_exec);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

void	handler_quit_exec(int signum)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = 128 + signum;
}

void	handler_int_exec(int signum)
{
	(void)signum;
	g_exit_status = 130;
}

void	handler_int(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}
