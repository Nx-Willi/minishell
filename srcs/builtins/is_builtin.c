/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:41:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 13:32:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_infos *infos)
{
	if (_strcmp(infos->cmd_name, "echo") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "cd") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "pwd") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "export") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "unset") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "env") == TRUE)
		return (TRUE);
	else if (_strcmp(infos->cmd_name, "exit") == TRUE)
		return (TRUE);
	return (FALSE);
}
