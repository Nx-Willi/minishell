/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:19:06 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:15:29 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Know how many chars takes n
static int	ft_sizebuffer(long int n, int basesize)
{
	int	chars;

	if (n == 0)
		return (1);
	chars = 0;
	if (n < 0)
	{
		n = -n;
		chars++;
	}
	while (n > 0)
	{
		n /= basesize;
		chars++;
	}
	return (chars);
}

static int	is_base_correct(char *base)
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

char	*ft_itoa_base(int nbr, char *base)
{
	int		i_basesize;
	char	*s_nbr;
	long	li_nbr;

	i_basesize = ft_strlen(base);
	if (i_basesize <= 1 || !is_base_correct(base))
		return ("0");
	li_nbr = nbr;
	nbr = ft_sizebuffer(li_nbr, i_basesize);
	s_nbr = malloc(sizeof(char) * (nbr + 1));
	if (s_nbr == NULL)
		return (NULL);
	s_nbr[nbr--] = '\0';
	s_nbr[nbr] = base[0];
	if (li_nbr < 0)
	{
		s_nbr[0] = '-';
		li_nbr = -li_nbr;
	}
	while (li_nbr > 0)
	{
		s_nbr[nbr--] = base[li_nbr % i_basesize];
		li_nbr /= i_basesize;
	}
	return (s_nbr);
}
