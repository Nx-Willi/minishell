/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:26:25 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/25 17:05:11 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	int		i;
	t_env	*sorted_env;

	sorted_env = env;
	sort_env(sorted_env);
	while (sorted_env)
	{
		i = 0;
		ft_putstr("declare -x ");
		while (sorted_env->variable[i] != '\0'
			&& sorted_env->variable[i] != '=')
			ft_putchar(sorted_env->variable[i++]);
		ft_putstr("=\"");
		i++;
		ft_putstr(sorted_env->variable + i);
		ft_putstr("\"\n");
		sorted_env = sorted_env->next;
	}
}
