/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:45:33 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:46:21 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t			n;
	unsigned char	*buffer_dst;
	unsigned char	*buffer_src;

	buffer_dst = (unsigned char *)dst;
	buffer_src = (unsigned char *)src;
	if (!buffer_dst && !buffer_src)
		return (NULL);
	n = 0;
	if (buffer_dst > buffer_src)
		while (size-- > 0)
			buffer_dst[size] = buffer_src[size];
	else
	{
		while (n < size)
		{
			buffer_dst[n] = buffer_src[n];
			n++;
		}
	}
	return (dst);
}
