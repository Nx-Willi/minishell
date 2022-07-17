/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:53:40 by wdebotte          #+#    #+#             */
/*   Updated: 2022/01/08 18:45:46 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*buffer_lst;
	t_list	*begin;

	(void)del;
	if (lst == NULL)
		return (NULL);
	begin = 0;
	while (lst != NULL)
	{
		if (!begin)
		{
			buffer_lst = ft_lstnew(f(lst->content));
			begin = buffer_lst;
		}
		else
		{
			buffer_lst->next = ft_lstnew(f(lst->content));
			buffer_lst = buffer_lst->next;
		}
		lst = lst->next;
	}
	return (begin);
}
