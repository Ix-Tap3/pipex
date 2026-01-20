/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:23:06 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/22 00:42:29 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_tmp;
	t_list	*node;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	lst_tmp = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		node = ft_lstnew(tmp);
		if (node == NULL)
		{
			del(tmp);
			ft_lstclear(&lst_tmp, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_tmp, node);
		lst = lst->next;
	}
	return (lst_tmp);
}
