/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:55:50 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:47:38 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	size_dst;

	size_dst = ft_strlen(dst);
	i = size_dst;
	if (i >= size)
		return (size + ft_strlen(src));
	n = -1;
	while (src[++n] != '\0' && i + n < size - 1)
		dst[i + n] = src[n];
	if (i + n < size)
		dst[i + n] = '\0';
	return (i + ft_strlen(src));
}
