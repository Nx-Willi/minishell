/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/09 18:31:17 by wdebotte         ###   ########.fr       */
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
	infos->env = NULL;
	infos->cmd = NULL;
	cpy_env_to_lst(infos, envp);
	cpy_env_to_char(infos);
	if (is_var_in_env(infos->env, "PWD") == FALSE)
		set_pwd_var(infos);
}

static int	get_line_infos(t_infos *infos)
{
	infos->prompt = readline(SH_NAME"$ ");
	if (infos->prompt == NULL)
	{
		exit_program(EXIT_SUCCESS);
		return (FALSE);
	}
	if (!is_str_clear(infos->prompt))
		add_history(infos->prompt);
	else
	{
		free(infos->prompt);
		return (FALSE);
	}
	infos->cmd = parsing(infos, infos->prompt);
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
		if (!is_builtin(infos.cmd->argv[0]))
			exec_simple(&infos, infos.cmd);
		else
			exec_builtin(&infos, infos.cmd);
		free(infos.prompt);
		infos.prompt = NULL;
		free_cmd(infos.cmd);
	}
	return (0);
}
