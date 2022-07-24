/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/23 16:55:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void	get_signals(void)
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

static void	init_main(t_infos *infos, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	get_signals();
	infos->envp = NULL;
	infos->env = NULL;
	infos->cmd = NULL;
	cpy_env_to_lst(infos, envp);
	if (is_var_in_env(infos->env, "PWD") == FALSE)
		set_pwd_var(infos);
	set_shlvl_var(infos);
	cpy_env_to_char(infos);
}

static int	get_line_infos(t_infos *infos)
{
	infos->prompt = readline(SH_NAME"$ ");
	if (infos->prompt == NULL)
	{
		ft_putstr("exit\n");
		exit_program(infos, EXIT_SUCCESS);
		return (FALSE);
	}
	if (!is_str_clear(infos->prompt))
		add_history(infos->prompt);
	else
		return (FALSE);
	infos->cmd = parsing(infos, infos->prompt);
	if (infos->cmd == NULL)
	{
		g_exit_status = 2;
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	print_message(argv[0]);
	init_main(&infos, argc, argv, envp);
	while (1)
	{
		if (get_line_infos(&infos) == TRUE)
		{
			exec_commands(&infos);
			free_cmd(infos.cmd);
			infos.cmd = NULL;
		}
		free(infos.prompt);
		infos.prompt = NULL;
	}
	return (0);
}
