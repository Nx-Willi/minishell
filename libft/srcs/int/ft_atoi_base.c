/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:59:15 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/04 17:56:56 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_whitespace(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	is_base_correct(const char *base)
{
	int	i;
	int	n;

	i = 0;
	if (base[i] == '+' || base[i] == '-' || ft_isspace(base[i]))
		return (0);
	while (base[i] != '\0')
	{
		n = 1;
		while (base[i + n] != '\0')
		{
			if (base[i + n] == '+' || base[i + n] == '-'
				|| ft_isspace(base[i + n]) || base[i + n] == base[i])
				return (0);
			n++;
		}
		i++;
	}
	return (1);
}

static int	ft_get_base_pos(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int			i_basesize;
	int			i_negativ;
	long int	li_number;

	i_basesize = ft_strlen(base);
	if (i_basesize <= 1 || !is_base_correct(base))
		return (0);
	li_number = 0;
	i_negativ = 1;
	while (*str && ft_is_whitespace(*str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		if (*(str++) == '-')
			i_negativ = -i_negativ;
	while (*str)
		li_number = li_number * i_basesize + ft_get_base_pos(*str++, base);
	return (li_number * i_negativ);
}
