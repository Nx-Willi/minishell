/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:26:25 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/17 21:32:41 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterror(char *arg)
{
	ft_putstr_fd(SH_NAME": export: ", 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	print_env(t_env *env)
{
	int	i;

	while (env != NULL)
	{
		i = 0;
		ft_putstr("declare -x ");
		while (env->variable[i] != '=')
			ft_putchar(env->variable[i++]);
		ft_putstr("=\"");
		i++;
		ft_putstr(env->variable + i);
		ft_putstr("\"\n");
		env = env->next;
	}
}
