/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/25 16:51:19 by wdebotte         ###   ########.fr       */
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
	cpy_env(&infos.env, envp);
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
		else
		{
			free(infos.line);
			continue ;
		}
	//	infos.argv = get_command_args(infos.line);
		if (!is_builtin(infos.line))
			exec_simple(&infos);
		else
			exec_builtin(&infos);
		free(infos.line);
		infos.line = NULL;
	}
	free_env(infos.env);
	return (0);
}
