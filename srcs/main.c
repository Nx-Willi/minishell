/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/19 18:53:42 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*path;
	char	*line;

	while (1)
	{
		line = readline(">$ ");
		path = get_command_path(line);
		if (path == NULL)
			printf("%s: command not found\n", line);
		else
			exec_simple(path);
		free(path);
		free(line);
		line = NULL;
	}
	return (0);
}
