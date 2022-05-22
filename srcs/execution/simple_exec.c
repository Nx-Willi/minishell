/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:13 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/22 14:32:42 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_command_args(char *line)
{
	char	**argv;

	argv = ft_split(line, ' ');
	return (argv);
}

void	exec_simple(char *line)
{
	pid_t	child_pid;
	pid_t	tmp_pid;
	char	*cmd;
	char	**argv;

	cmd = get_command_path(line);
	argv = get_command_args(line);
	tmp_pid = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd, argv, (void*)0);
		printf("%s: command not found\n", cmd);
		free(cmd);
		free_char_tab(argv);
		exit(0);
	}
	else
	{
		while (tmp_pid != child_pid)
			tmp_pid = wait(NULL);
		free(cmd);
		free_char_tab(argv);
		return ;
	}
}
