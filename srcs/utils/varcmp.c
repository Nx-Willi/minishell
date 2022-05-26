/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 15:44:11 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varcmp(char *env_var, char *var)
{
	size_t	i;

	i = 0;
	while (env_var[i] != '\0' && env_var[i] != '=')
		i++;
	if (i != ft_strlen(var))
		return (FALSE);
	i = 0;
	while (env_var[i] != '\0' && var[i] != '\0')
	{
		if (env_var[i] != var[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
