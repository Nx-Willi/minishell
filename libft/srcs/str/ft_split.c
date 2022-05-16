/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:45:24 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:19:28 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	ft_strcountwords(char const *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			words++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (words);
}

static char	*ft_strsplitdup(const char *str, char c)
{
	int		i;
	char	*buffer;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	buffer = malloc(sizeof(char) * (i + 1));
	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	**ft_split(char const *str, char c)
{
	int			i;
	int			n;
	int			words;
	char		**tab_buffer;

	if (str == NULL)
		return (NULL);
	words = ft_strcountwords(str, c);
	tab_buffer = malloc(sizeof(char *) * (words + 1));
	if (tab_buffer == NULL)
		return (NULL);
	i = 0;
	n = 0;
	while (str[i] != '\0' && n < words)
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		tab_buffer[n] = ft_strsplitdup(str + i, c);
		if (tab_buffer[n++] == NULL)
			return (ft_freetab(tab_buffer));
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	tab_buffer[n] = NULL;
	return (tab_buffer);
}
