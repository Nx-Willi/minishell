/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:54:19 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/15 13:25:37 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	builtin_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putstr(buffer);
	ft_putchar('\n');
	free(buffer);
	g_exit_status = SUCCESS;
}
