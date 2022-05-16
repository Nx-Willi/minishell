/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:05:04 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:46:05 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buffer_s;

	buffer_s = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*buffer_s == (unsigned char)c)
			return (buffer_s);
		buffer_s++;
	}
	return (NULL);
}
