/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:26:25 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/24 16:47:50 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int	i;

	while (env != NULL)
	{
		i = 0;
		ft_putstr("declare -x ");
		while (env->variable[i] != '\0' && env->variable[i] != '=')
			ft_putchar(env->variable[i++]);
		ft_putstr("=\"");
		i++;
		ft_putstr(env->variable + i);
		ft_putstr("\"\n");
		env = env->next;
	}
}
