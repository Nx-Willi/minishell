/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:57:41 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/25 16:52:45 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_infos *infos, char **argv)
{
	int		i;

	i = 1;
	while (argv[i] != NULL)
		add_env_var(infos->env, argv[i++]);
}
