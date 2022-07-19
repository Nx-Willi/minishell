/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:40:06 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/19 14:27:49 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	open_dir(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(SH_NAME": cd: No such file or directory\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(SH_NAME": cd: Permission denied\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd(SH_NAME": cd: Not a directory\n", 2);
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
		open_dir(get_env_var_value(cmd->infos, "HOME"));
	current_workdir = getcwd(NULL, 0);
	if (cmd->argv[1][0] == '~')
		path_to = fill_command_path(current_workdir, cmd->argv[1] + 1);
	else
		path_to = fill_command_path(current_workdir, cmd->argv[1]);
	open_dir(path_to);
	free(current_workdir);
	free(path_to);
}

static void	change_directory(t_cmd *cmd, char *path_home)
{
	char	*oldpwd_var;

	if (cmd->argv[1] == NULL)
		open_dir(path_home);
	else if (cmd->argv[1][0] == '/')
		open_dir(cmd->argv[1]);
	else if (_strcmp(cmd->argv[1], "-") == TRUE)
	{
		oldpwd_var = get_env_var_value(cmd->infos, "OLDPWD");
		if (oldpwd_var != NULL)
		{
			ft_putstr(oldpwd_var);
			ft_putchar('\n');
			open_dir(oldpwd_var);
		}
		else
		{
			ft_putstr_fd(SH_NAME": cd: OLDPWD not set\n", 2);
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
		ft_putstr_fd(SH_NAME": cd: HOME not set\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	if (cmd->argv[1] != NULL && cmd->argv[2] != NULL)
	{
		ft_putstr_fd(SH_NAME": cd: too many arguments\n", 2);
		g_exit_status = FAILURE;
		return ;
	}
	buffer = getcwd(NULL, 0);
	change_directory(cmd, path_home);
	set_oldpwd_var(cmd->infos, buffer);
	set_pwd_var(cmd->infos);
	free(buffer);
}
