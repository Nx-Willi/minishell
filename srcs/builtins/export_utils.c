/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:26:25 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/28 16:19:17 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(t_env *sorted_env)
{
	int	i;

	i = 0;
	ft_putstr("declare -x ");
	while (sorted_env->variable[i] != '\0'
		&& sorted_env->variable[i] != '=')
		ft_putchar(sorted_env->variable[i++]);
	if (sorted_env->variable[i] == '=')
	{
		ft_putstr("=\"");
		i++;
		ft_putstr(sorted_env->variable + i);
		ft_putchar('\"');
	}
	ft_putchar('\n');
}

void	print_env(t_env *env)
{
	t_env	*tmp;
	t_env	*sorted_env;

	tmp = env;
	sorted_env = sort_env(tmp);
	tmp = sorted_env;
	if (sorted_env == NULL)
		return ;
	while (sorted_env)
	{
		print_var(sorted_env);
		sorted_env = sorted_env->next;
	}
	free_env(tmp);
}
