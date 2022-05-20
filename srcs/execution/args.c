/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:07:35 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/20 15:13:07 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_command_args(char *line, char *cmd)
{
	char	**argv;

	argv = ft_split(line, ' ');
	if (argv == NULL)
		return (NULL);
	free(argv[0]);
	argv[0] = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (argv[0] == NULL)
		return (NULL);
	ft_strlcpy(argv[0], cmd, ft_strlen(cmd));
	return (argv);
}


//{ cmd, args1, args2, args3, NULL }
