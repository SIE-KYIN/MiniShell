/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 11:13:32 by gshim             #+#    #+#             */
/*   Updated: 2021/07/26 19:15:08 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
	{
		ft_lstclear(&start, del);
		return (0);
	}
	start = new;
	while (lst->next)
	{
		new->next = ft_lstnew(f(lst->next->content));
		if (!(new->next))
		{
			ft_lstclear(&start, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	return (start);
}
