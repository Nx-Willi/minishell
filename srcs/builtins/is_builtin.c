/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:19:01 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/19 10:55:53 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	int	i;

	i = 0;
	while (command[i] != '\0' && command[i] != '\n' && command[i] != ' ')
		i++;
	if (ft_strncmp(command, "echo", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "cd", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "pwd", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "export", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "unset", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "env", i) == 0)
		return (TRUE);
	else if (ft_strncmp(command, "exit", i) == 0)
		return (TRUE);
	return (FALSE);
}
