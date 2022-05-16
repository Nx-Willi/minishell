/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:15:16 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/05 22:47:17 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_arg(va_list list, char arg)
{
	if (arg == 'c')
		return (_putchar(va_arg(list, int)));
	else if (arg == 's')
		return (_putstr(va_arg(list, char *)));
	else if (arg == 'p')
		return (_putstr("0x")
			+ _putnbr_hexa_ullint(va_arg(list, unsigned long long), 0));
	else if (arg == 'd' || arg == 'i')
		return (_putnbr(va_arg(list, int), 0));
	else if (arg == 'u')
		return (_putnbr_uint(va_arg(list, unsigned), 0));
	else if (arg == 'x')
		return (_putnbr_hexa(va_arg(list, int), HEXA, 0));
	else if (arg == 'X')
		return (_putnbr_hexa(va_arg(list, int), HEXA_CAPS, 0));
	else if (arg == '%')
		return (_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	list;

	va_start(list, str);
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%' && is_valid_arg(*(str + 1)))
			count += print_arg(list, *(++str));
		else
			count += _putchar(*str);
		str++;
	}
	va_end(list);
	return (count);
}
