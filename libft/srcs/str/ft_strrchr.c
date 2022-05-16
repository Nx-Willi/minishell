/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:00 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:48:04 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*buffer_str;

	if ((unsigned char)c == '\0')
		return ((char *)str + ft_strlen(str));
	buffer_str = (char *)str;
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			buffer_str = (char *)str;
		str++;
	}
	if (*str == (unsigned char)c || *buffer_str == (unsigned char)c)
		return (buffer_str);
	return ((char *) NULL);
}
