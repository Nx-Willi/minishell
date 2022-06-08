/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:06:33 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 17:52:38 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		n;
	char	*buffer;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (buffer == NULL)
		return (NULL);
	i = -1;
	n = -1;
	while (s1[++i] != '\0')
		buffer[i] = s1[i];
	while (s2[++n] != '\0')
		buffer[i + n] = s2[n];
	buffer[i + n] = '\0';
	return (buffer);
}
