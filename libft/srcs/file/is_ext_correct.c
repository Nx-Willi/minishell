/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ext_correct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:26:38 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 22:53:10 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ext must be preceded by '.'
int	is_ext_correct(const char *file, const char *ext)
{
	size_t	i;
	size_t	len_ext;

	i = ft_strlen(file) - 1;
	if (file == NULL || ext == NULL || i == 0)
		return (0);
	while (file[i] && file[i] != '.' && i > 0)
		i--;
	len_ext = ft_strlen(ext);
	if (file[i] != '.' || ft_strlen(file + i) != len_ext)
		return (0);
	if (ft_strncmp(file + i, ext, len_ext) == 0)
		return (1);
	return (0);
}
