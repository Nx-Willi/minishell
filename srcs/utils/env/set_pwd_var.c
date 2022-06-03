/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:45:48 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/03 13:45:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd_var(t_infos *infos)
{
	int			i[2];
	char		*curdir;
	static char	path[] = "";

	curdir = getcwd(NULL, 0);
	if (curdir == NULL)
		return ;
	path[0] = '\0';
	ft_strlcat(path, "PWD=", 5);
	i[0] = 4;
	i[1] = -1;
	while (curdir[++i[1]] != '\0')
		path[i[0] + i[1]] = curdir[i[1]];
	path[i[0] + i[1]] = '\0';
	add_env_var(infos, path, FALSE);
	free(curdir);
}

void	set_oldpwd_var(t_infos *infos)
{
	int			i[2];
	char		*curdir;
	static char	path[] = "";

	curdir = getcwd(NULL, 0);
	if (curdir == NULL)
		return ;
	path[0] = '\0';
	ft_strlcat(path, "OLDPWD=", 8);
	i[0] = 7;
	i[1] = -1;
	while (curdir[++i[1]] != '\0')
		path[i[0] + i[1]] = curdir[i[1]];
	path[i[0] + i[1]] = '\0';
	add_env_var(infos, path, FALSE);
	free(curdir);
}
