/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:20:36 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:19:34 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*buffer;

	buffer = malloc(sizeof(const char) * (ft_strlen(s) + 1));
	if (buffer == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		buffer[i] = s[i];
	buffer[i] = '\0';
	return (buffer);
}
