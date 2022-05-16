/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:13:07 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/05 23:01:25 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define FALSE		0
# define TRUE		1
# define HEXA		"0123456789abcdef"
# define HEXA_CAPS	"0123456789ABCDEF"

int	ft_printf(const char *str, ...);
int	_putchar(char c);
int	_strlen(char *str);
int	_putstr(char *str);
int	_putnbr(int nb, int count);
int	_putnbr_uint(unsigned int nbr, int count);
int	_putnbr_hexa(int nb, char *base, int count);
int	_putnbr_hexa_ullint(unsigned long long int nbr, int count);
int	is_valid_arg(char c);

#endif
