/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/24 14:55:29 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		line = readline(">$ ");
		if (line == NULL)
		{
			ft_putstr("exit\n");
			return (exit_program(2));
		}
		if (line[0] != '\0')
			add_history(line);
		exec_simple(line);
		free(line);
		line = NULL;
	}
	return (0);
}
