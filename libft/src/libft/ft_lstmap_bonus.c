/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohchoi <bohchoi@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:25:28 by bohchoi           #+#    #+#             */
/*   Updated: 2024/03/20 20:06:22 by bohchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst-> content));
	tmp = new;
	lst = lst-> next;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst-> content));
		tmp = tmp-> next;
		lst = lst-> next;
		if (tmp == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
	}
	return (new);
}
