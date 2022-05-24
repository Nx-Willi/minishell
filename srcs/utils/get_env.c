/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:42:43 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/24 18:31:23 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_list *env, char **env_from)
{
	env = NULL;
	if (env_from == NULL)
		return ;
	while (*env_from != NULL)
	{
		if (env == NULL)
			env = ft_lstnew((char *)*env_from);
		/*else
			ft_lstadd_back(&env, ft_lstnew((char *)*env_from));*/
		env_from++;
	}
}
