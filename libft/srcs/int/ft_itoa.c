/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:35:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:15:34 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Know how many chars takes n
static int	ft_sizebuffer(long int n)
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
		n /= 10;
		chars++;
	}
	return (chars);
}

char	*ft_itoa(int n)
{
	char		*number;
	long int	long_n;

	long_n = n;
	n = ft_sizebuffer(long_n);
	number = malloc(sizeof(char) * (n + 1));
	if (number == NULL)
		return (NULL);
	number[n--] = '\0';
	if (long_n == 0)
	{
		number[n] = 48;
		return (number);
	}
	if (long_n < 0)
	{
		number[0] = '-';
		long_n = -long_n;
	}
	while (long_n > 0)
	{
		number[n--] = long_n % 10 + 48;
		long_n /= 10;
	}
	return (number);
}
