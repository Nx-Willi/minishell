/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 14:15:39 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void	set_shlvl_var(t_infos *infos)
{
	int		old_shlvl;
	char	*new_shlvl;
	char	*new_var;
	char	buffer[7];

	if (is_var_in_env(infos->env, "SHLVL") == FALSE)
	{
		add_env_var(infos, "SHLVL=1", FALSE);
		return ;
	}
	old_shlvl = ft_atoi(get_env_var_value(infos, "SHLVL"));
	old_shlvl++;
	new_shlvl = ft_itoa(old_shlvl);
	buffer[0] = '\0';
	ft_strlcat(buffer, "SHLVL=", 7);
	new_var = ft_strjoin(buffer, new_shlvl);
	free(new_shlvl);
	add_env_var(infos, new_var, FALSE);
	free(new_var);
}

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
	set_shlvl_var(infos);
	cpy_env_to_char(infos);
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
		return (FALSE);
	infos->cmd = parsing(infos, infos->prompt);
	if (infos->cmd == NULL)
	{
		g_exit_status = 2;
		return (FALSE);
	}
	return (TRUE);
}

static void	exec_commands(t_infos *infos)
{
	if (infos->npipes == 0)
	{
		if (is_builtin(infos->cmd->argv[0]))
			redir_builtin(infos->cmd);
		else
			exec_simple(infos->cmd);
	}
	else
		exec_pipes(infos);
}

int	main(int argc, char **argv, char **envp)
{
	t_infos	infos;

	init_main(&infos, argc, argv, envp);
	while (1)
	{
		if (get_line_infos(&infos) == TRUE)
		{
			exec_commands(&infos);
			free_cmd(infos.cmd);
		}
		free(infos.prompt);
		infos.prompt = NULL;
	}
	return (0);
}
