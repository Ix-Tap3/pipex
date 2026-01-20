/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:40:16 by pcaplat           #+#    #+#             */
/*   Updated: 2025/11/07 10:26:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int	i;
	int	j;

	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	ft_putuint_base_rec(unsigned int nbr, char *base, int fd)
{
	int	base_type;

	base_type = ft_strlen(base);
	if (nbr >= (unsigned int)base_type)
	{
		ft_putuint_base_rec(nbr / base_type, base, fd);
		ft_putuint_base_rec(nbr % base_type, base, fd);
	}
	else
		ft_putchar_fd(base[nbr], fd);
}

void	ft_putuint_base_fd(unsigned int nbr, char *base, int fd)
{
	if (check_base(base) == 0)
		return ;
	ft_putuint_base_rec(nbr, base, fd);
}
