/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:40:06 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 12:51:06 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	open_dir(t_cmd *cmd, char *path)
{
	if (access(path, F_OK) == -1)
	{
		puterror(cmd, cmd->argv[1], "No such file or directory");
		g_exit_status = FAILURE;
		return ;
	}
	if (access(path, X_OK) == -1)
	{
		puterror(cmd, cmd->argv[1], "Permission denied");
		g_exit_status = FAILURE;
		return ;
	}
	if (chdir(path) == -1)
	{
		puterror(cmd, cmd->argv[1], "Not a directory");
		g_exit_status = FAILURE;
	}
	else
		g_exit_status = SUCCESS;
}

static void	change_wcurdir(t_cmd *cmd)
{
	char	*path_to;
	char	*current_workdir;

	if (cmd->argv[1][0] == '~')
		open_dir(cmd, get_env_var_value(cmd->infos, "HOME"));
	current_workdir = getcwd(NULL, 0);
	if (cmd->argv[1][0] == '~')
		path_to = fill_command_path(current_workdir, cmd->argv[1] + 1);
	else if (current_workdir != NULL)
		path_to = fill_command_path(current_workdir, cmd->argv[1]);
	else
	{
		puterror(cmd, cmd->argv[1], "No such file or directory");
		g_exit_status = FAILURE;
		return ;
	}
	open_dir(cmd, path_to);
	free(current_workdir);
	free(path_to);
}

static void	change_directory(t_cmd *cmd, char *path_home)
{
	char	*oldpwd_var;

	if (cmd->argv[1] == NULL)
		open_dir(cmd, path_home);
	else if (cmd->argv[1][0] == '/')
		open_dir(cmd, cmd->argv[1]);
	else if (_strcmp(cmd->argv[1], "-") == TRUE)
	{
		oldpwd_var = get_env_var_value(cmd->infos, "OLDPWD");
		if (oldpwd_var != NULL)
		{
			ft_putstr(oldpwd_var);
			ft_putchar('\n');
			open_dir(cmd, oldpwd_var);
		}
		else
		{
			puterror(cmd, NULL, "OLDPWD not set");
			g_exit_status = FAILURE;
		}
	}
	else
		change_wcurdir(cmd);
}

void	builtin_cd(t_cmd *cmd)
{
	char	*path_home;
	char	*buffer;

	path_home = get_env_var_value(cmd->infos, "HOME");
	if (path_home == NULL)
	{
		puterror(cmd, NULL, "HOME not set");
		g_exit_status = FAILURE;
		return ;
	}
	if (cmd->argv[1] != NULL && cmd->argv[2] != NULL)
	{
		puterror(cmd, NULL, "too many arguments");
		g_exit_status = FAILURE;
		return ;
	}
	buffer = getcwd(NULL, 0);
	change_directory(cmd, path_home);
	set_oldpwd_var(cmd->infos, buffer);
	set_pwd_var(cmd->infos);
	free(buffer);
}
