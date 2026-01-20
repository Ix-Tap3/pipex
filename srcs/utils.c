/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:26:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/20 18:44:34 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*str_catsep(char *s1, char *s2, char sep)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	free_lst(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if ((char **)lst->content)
			ft_freestrar((char **)lst->content);
		free(lst);
		lst = next;
	}
}

void	ft_puterror(char *error_msg)
{
	if (!error_msg)
	{
		perror("Error ");
		exit(1);
	}
	ft_putstr_fd(error_msg, 2);
	exit(1);
}
