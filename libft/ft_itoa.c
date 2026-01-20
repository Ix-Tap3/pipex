/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:53:33 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/19 16:00:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buf[12];
	char	*curs;
	char	*res;
	long	t;

	t = n;
	buf[11] = '\0';
	curs = &buf[10];
	while (t)
	{
		if (n < 0)
			*curs-- = (-t % 10) + '0';
		else
			*curs-- = (t % 10) + '0';
		if (t > -10 && t < 0)
			*curs-- = '-';
		t /= 10;
	}
	if (curs == &buf[10])
		*curs-- = '0';
	res = ft_strdup(curs + 1);
	return (res);
}
