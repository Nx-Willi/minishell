/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:46:53 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/02 14:44:17 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_command_path(char *start_path, char *end_path)
{
	int		i;
	int		n;
	char	*buffer;

	buffer = malloc(sizeof(char) * (ft_strlen(start_path)
				+ ft_strlen(end_path) + 2));
	if (buffer == NULL)
		return (NULL);
	i = -1;
	while (start_path[++i] != '\0')
		buffer[i] = start_path[i];
	buffer[i++] = '/';
	n = i;
	i = -1;
	while (end_path[++i] != '\0')
		buffer[n + i] = end_path[i];
	buffer[n + i] = '\0';
	return (buffer);
}
