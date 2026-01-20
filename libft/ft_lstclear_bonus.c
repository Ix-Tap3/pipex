/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:19:47 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/19 19:26:00 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	lst_tmp = *lst;
	while (lst_tmp)
	{
		next_node = lst_tmp->next;
		del(lst_tmp->content);
		free(lst_tmp);
		lst_tmp = next_node;
	}
	*lst = NULL;
}
