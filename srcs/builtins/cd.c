/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:40:06 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/27 17:12:40 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_infos *infos)
{
	char	*path_home;
	char	*path_to;

	path_home = get_env_var_value(infos, "HOME");
	if (path_home == NULL)
		return ;
	if (infos->argv[1] == NULL)
		chdir(path_home);
	else
	{
		path_to = fill_command_path(path_home, infos->argv[1]);
		char *toto = malloc(sizeof(char) * 254);
		printf("%s\n", getwd(toto));
		//chdir(path_to);
	}
}
