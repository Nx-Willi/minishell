/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:48:00 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:48:00 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = -1;
	while (s1[++i] != '\0' && i < n)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while ((s1[i + j] != '\0' && s2[j] != '\0')
				&& s1[i + j] == s2[j] && i + j < n)
				j++;
			if (s2[j] == '\0')
				return ((char *)s1 + i);
		}
	}
	return (NULL);
}
