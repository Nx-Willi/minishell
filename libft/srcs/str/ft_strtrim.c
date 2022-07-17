/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:10:28 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:19:54 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, char const *charset)
{
	while (*charset != '\0')
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *charset)
{
	int		i;
	int		start;
	int		end;
	char	*buffer;

	if (str == NULL)
		return (NULL);
	if (charset == NULL)
		return (ft_strdup(str));
	i = 0;
	while (str[i] != '\0' && ft_is_charset(str[i], charset))
		i++;
	start = i;
	i = ft_strlen(str) - 1;
	while (i >= start && ft_is_charset(str[i], charset))
		i--;
	end = i;
	buffer = (char *)malloc(sizeof(char) * (end - start + 2));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		buffer[i++] = str[start++];
	buffer[i] = '\0';
	return (buffer);
}
