/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:34:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/27 14:39:00 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	get_signals(void)
{
	struct sigaction	s_action_quit;
	struct sigaction	s_action_int;

	sigemptyset(&s_action_quit.sa_mask);
	s_action_quit.sa_sigaction = &handler_quit;
	s_action_quit.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &s_action_quit, NULL);
	sigemptyset(&s_action_int.sa_mask);
	s_action_int.sa_sigaction = &handler_int;
	s_action_int.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_action_int, NULL);
}

void	handler_quit(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid == 0)
	{
		ft_putstr_fd("Quit (code dumped)\n", 2);
		g_exit_status = 128 + signum;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 0);
}

void	handler_int(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	if (info->si_pid == 0)
		ft_putchar('\n');
	else
	{
		ft_putstr("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_exit_status = 130;
}
