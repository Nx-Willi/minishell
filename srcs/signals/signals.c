/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:34:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/23 17:47:55 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
