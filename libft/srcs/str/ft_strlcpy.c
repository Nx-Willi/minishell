/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:32:32 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:47:42 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	if (size > 0)
	{
		n = -1;
		while (src[++n] != '\0' && n < size - 1)
			dst[n] = src[n];
		dst[n] = '\0';
	}
	return (ft_strlen(src));
}
