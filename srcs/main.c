/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:54:03 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/19 10:10:57 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
We can use readline() function but it does a lot of leaks
char *readline(const char *prompt);
*/
int	main(void)
{
	char	*line;

	while (1)
	{
		_putstr(">$ ");
		line = get_next_line(0);
		printf("%s", line);
		free(line);
		line = NULL;
	}
	return (0);
}
