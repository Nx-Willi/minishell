/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:23:54 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:45:26 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer_lst;

	while (*lst != NULL)
	{
		buffer_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = buffer_lst;
	}
}
