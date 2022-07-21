/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:33:20 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 14:33:43 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl_var(t_infos *infos)
{
	int		old_shlvl;
	char	*new_shlvl;
	char	*new_var;
	char	buffer[7];

	if (is_var_in_env(infos->env, "SHLVL") == FALSE)
	{
		add_env_var(infos, "SHLVL=1", FALSE);
		return ;
	}
	old_shlvl = ft_atoi(get_env_var_value(infos, "SHLVL"));
	old_shlvl++;
	new_shlvl = ft_itoa(old_shlvl);
	buffer[0] = '\0';
	ft_strlcat(buffer, "SHLVL=", 7);
	new_var = ft_strjoin(buffer, new_shlvl);
	free(new_shlvl);
	add_env_var(infos, new_var, FALSE);
	free(new_var);
}
