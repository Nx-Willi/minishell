/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:35:35 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/05 23:01:44 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	_putnbr(int nb, int count)
{
	long int	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		count += _putchar('-');
		nbr = -nbr;
	}
	if (nbr < 10)
		_putchar(nbr + '0');
	else
	{
		count = _putnbr(nbr / 10, count);
		_putchar(nbr % 10 + '0');
	}
	return (++count);
}

int	_putnbr_uint(unsigned int nbr, int count)
{
	if (nbr < 10)
		_putchar(nbr + '0');
	else
	{
		count = _putnbr_uint(nbr / 10, count);
		_putchar(nbr % 10 + '0');
	}
	return (++count);
}

int	_putnbr_hexa(int nb, char *base, int count)
{
	unsigned int	nbr;

	nbr = nb;
	if (nbr < 16)
		_putchar(base[nbr]);
	else
	{
		count = _putnbr_hexa(nbr / 16, base, count);
		_putchar(base[nbr % 16]);
	}
	return (++count);
}

int	_putnbr_hexa_ullint(unsigned long long int nbr, int count)
{
	if (nbr < 16)
		_putchar(HEXA[nbr]);
	else
	{
		count = _putnbr_hexa_ullint(nbr / 16, count);
		_putchar(HEXA[nbr % 16]);
	}
	return (++count);
}
