/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:56:47 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/22 17:57:58 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	tmp = (char *)s;
	i = 0;
	while (tmp[i])
		i++;
	if ((unsigned char)c == '\0')
		return (&tmp[i]);
	while (i >= 0)
	{
		if (tmp[i] == (unsigned char)c)
			return (&tmp[i]);
		i--;
	}
	return (NULL);
}
