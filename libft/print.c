/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 07:48:13 by pcaplat           #+#    #+#             */
/*   Updated: 2025/11/07 10:26:32 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putulong_fd(unsigned long n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	print_char(char c, int *len)
{
	ft_putchar_fd(c, 1);
	*len += 1;
}

void	print_str(char *s, int *len)
{
	if (!s)
	{
		*len += ft_strlen("(null)");
		ft_putstr_fd("(null)", 1);
		return ;
	}
	ft_putstr_fd(s, 1);
	*len += ft_strlen(s);
}

void	print_nb(int nb, int *len)
{
	ft_putnbr_fd(nb, 1);
	if (nb < 0)
		*len += 1;
	*len += ft_count_digits(nb);
}

void	print_uint(unsigned int nb, int *len)
{
	ft_putulong_fd((unsigned long)nb, 1);
	*len += ft_count_digits(nb);
}
