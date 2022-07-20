/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_control.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:27:42 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/20 16:51:05 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
	{
		cmd->fdin_tmp = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		cmd->fdout_tmp = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

void	clean_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
		dup2(cmd->fdin_tmp, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fdout_tmp, STDOUT_FILENO);
}
