/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:35:22 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/23 16:07:59 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_message_path(char *exec_path)
{
	char	*buffer;

	if (exec_path == NULL)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(exec_path) + 5));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	ft_strlcat(buffer, exec_path, ft_strlen(exec_path) - 8);
	ft_strlcat(buffer, ".message.txt", ft_strlen(buffer) + 13);
	return (buffer);
}

void	print_message(char *exec_path)
{
	int		fd;
	char	*str;
	char	*path;

	path = get_message_path(exec_path);
	if (path == NULL)
		return ;
	fd = open(path, O_RDONLY);
	free(path);
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
