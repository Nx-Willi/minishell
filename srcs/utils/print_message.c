/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:35:22 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 15:28:13 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_message(void)
{
	int		fd;
	char	*str;

	fd = open(".message.txt", O_RDONLY);
	if (fd == -1)
		return ;
	if (read(fd, NULL, 0) == -1)
		return ;
	ft_putstr(MSG_COLOR);
	ft_putchar('\n');
	str = get_next_line(fd);
	while (str != NULL)
	{
		ft_putstr(str);
		free(str);
		str = get_next_line(fd);
	}
	ft_putchar('\n');
	ft_putstr(BLANK);
	close(fd);
}
