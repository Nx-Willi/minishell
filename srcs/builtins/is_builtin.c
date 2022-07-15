/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:41:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 12:30:15 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (_strcmp(cmd_name, "echo") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "cd") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "pwd") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "export") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "unset") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "env") == TRUE)
		return (TRUE);
	else if (_strcmp(cmd_name, "exit") == TRUE)
		return (TRUE);
	return (FALSE);
}
