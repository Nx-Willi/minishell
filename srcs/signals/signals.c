/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:34:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/22 16:27:57 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	if (signum == CTRL_C)
	{
		ft_putstr("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
