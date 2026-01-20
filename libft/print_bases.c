/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:17:42 by pcaplat           #+#    #+#             */
/*   Updated: 2025/11/07 10:25:27 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex_diggit(unsigned long nb)
{
	int	dgt;

	dgt = 1;
	while (nb >= 16)
	{
		dgt++;
		nb /= 16;
	}
	return (dgt);
}

void	print_ptr(void *ptr, int *len)
{
	unsigned long	adress;

	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		*len += 5;
		return ;
	}
	adress = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	ft_putnbr_base_fd(adress, "0123456789abcdef", 1);
	*len += (count_hex_diggit(adress) + 2);
}

void	print_hex(unsigned int nbr, char c, int *len)
{
	if (c == 'x')
		ft_putuint_base_fd(nbr, "0123456789abcdef", 1);
	else if (c == 'X')
		ft_putuint_base_fd(nbr, "0123456789ABCDEF", 1);
	*len += count_hex_diggit(nbr);
}
