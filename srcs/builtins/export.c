/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:57:41 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 16:49:56 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *var)
{
	int	i;

	if (ft_strchr(var, '=') == NULL)
		return (FALSE);
	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (var[i] == '-' || var[i] == '*' || var[i] == '+')
		{
			printf("export: \'%s\': not a valid identifier\n", var);
			return (FALSE);
		}
		i++;
	}
	if (i == 0)
	{
		printf("export: \'%s\': not a valid identifier\n", var);
		return (FALSE);
	}
	return (TRUE);
}

void	builtin_export(t_infos *infos)
{
	int		i;

	i = 0;
	while (infos->argv[++i] != NULL)
		if (is_valid_identifier(infos->argv[i]) == TRUE)
			add_env_var(infos, infos->argv[i], FALSE);
	cpy_env_to_char(infos);
}
