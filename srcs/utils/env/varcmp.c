/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/30 15:46:30 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varcmp(char *var1, char *var2)
{
	size_t	i;
	size_t	n;

	i = 0;
	while (var1[i] != '\0' && var1[i] != '=')
		i++;
	n = 0;
	while (var2[n] != '\0' && var2[n] != '=')
		n++;
	if (i != n)
		return (FALSE);
	i = 0;
	while ((var1[i] != '\0' && var2[i] != '\0') && i <= n)
	{
		if (var1[i] != var2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
