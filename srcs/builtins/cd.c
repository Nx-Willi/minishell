/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:40:06 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/03 13:43:53 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_dir(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd(SH_NAME": cd: No such file or directory\n", 2);
		return ;
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(SH_NAME": cd: Permission denied\n", 2);
		return ;
	}
	if (chdir(path) == -1)
		ft_putstr_fd(SH_NAME": cd: Not a directory\n", 2);
}

static void	goto_curdir(t_infos *infos)
{
	char	*path_to;
	char	*current_workdir;

	current_workdir = getcwd(NULL, 0);
	path_to = fill_command_path(current_workdir, infos->argv[1]);
	open_dir(path_to);
	free(current_workdir);
	free(path_to);
}

void	builtin_cd(t_infos *infos)
{
	char	*path_home;

	path_home = get_env_var_value(infos, "HOME");
	if (path_home == NULL)
	{
		ft_putstr_fd(SH_NAME": cd: HOME not set\n", 2);
		return ;
	}
	if (infos->argv[1] != NULL && infos->argv[2] != NULL)
	{
		ft_putstr_fd(SH_NAME": cd: Can't move in more than one directory \
at the same time\n", 2);
		return ;
	}
	set_oldpwd_var(infos);
	if (infos->argv[1] == NULL)
		open_dir(path_home);
	else if (infos->argv[1][0] == '/')
		open_dir(infos->argv[1]);
	else
		goto_curdir(infos);
	set_pwd_var(infos);
}
