/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/03 14:15:42 by wdebotte         ###   ########.fr       */
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
	infos.envp = NULL;
	cpy_env_to_lst(&infos, envp);
	cpy_env_to_char(&infos);
	if (is_var_in_env(infos.env, "PWD") == FALSE)
		set_pwd_var(&infos);
	while (1)
	{
		infos.line = readline(SH_NAME"$ ");
		if (infos.line == NULL)
		{
			ft_putstr("exit\n");
			return (exit_program(&infos, 2, FALSE));
		}
		if (!is_str_clear(infos.line))
			add_history(infos.line);
		else
		{
			free(infos.line);
			continue ;
		}
		infos.cmd_name = get_cmd_name(infos.line);
		infos.cmd_path = get_command_path(infos.line);
		infos.argv = get_command_args(infos.line);
		if (!is_builtin(&infos))
			exec_simple(&infos);
		else
			exec_builtin(&infos);
		free(infos.line);
		infos.line = NULL;
		free(infos.cmd_name);
		free(infos.cmd_path);
		free_char_tab(infos.argv);
	}
	free(infos.envp);
	free_env(infos.env);
	return (0);
}
