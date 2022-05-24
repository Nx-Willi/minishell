/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/24 18:30:14 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	(void)envp;
	get_env(infos.env, envp);
	while (1)
	{
		infos.line = readline(">$ ");
		if (infos.line == NULL)
		{
			ft_putstr("exit\n");
			return (exit_program(2));
		}
		if (infos.line[0] != '\0')
			add_history(infos.line);
		exec_simple(&infos);
		free(infos.line);
		free_list(infos.env);
		infos.line = NULL;
	}
	return (0);
}
