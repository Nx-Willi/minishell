/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:37:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/07 15:47:58 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	long int	li_nbr;

	li_nbr = nbr;
	if (li_nbr < 0)
	{
		li_nbr = -li_nbr;
		ft_putchar('-');
	}
	if (li_nbr >= 10)
	{
		ft_putnbr(li_nbr / 10);
		ft_putchar(li_nbr % 10 + 48);
	}
	else
		ft_putchar(li_nbr + 48);
}
