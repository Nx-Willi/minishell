/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:54:19 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/20 18:00:09 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	builtin_pwd(t_infos *infos)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		ft_putstr(get_env_var_value(infos, "PWD"));
	else
	{
		ft_putstr(buffer);
		free(buffer);
	}
	ft_putchar('\n');
	g_exit_status = SUCCESS;
}
