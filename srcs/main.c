/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/03 14:36:38 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_main(t_infos *infos, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	infos->envp = NULL;
	cpy_env_to_lst(infos, envp);
	cpy_env_to_char(infos);
	if (is_var_in_env(infos->env, "PWD") == FALSE)
		set_pwd_var(infos);
}

static int	get_line_infos(t_infos *infos)
{
	infos->line = readline(SH_NAME"$ ");
	if (infos->line == NULL)
	{
		ft_putstr("exit\n");
		exit_program(infos, 2, FALSE);
		return (FALSE);
	}
	if (!is_str_clear(infos->line))
		add_history(infos->line);
	else
	{
		free(infos->line);
		return (FALSE);
	}
	infos->cmd_name = get_cmd_name(infos->line);
	infos->cmd_path = get_command_path(infos->line);
	infos->argv = get_command_args(infos->line);
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	init_main(&infos, argc, argv, envp);
	while (1)
	{
		if (get_line_infos(&infos) == FALSE)
			continue ;
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
