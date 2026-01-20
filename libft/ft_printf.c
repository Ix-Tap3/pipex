/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 05:00:56 by pcaplat           #+#    #+#             */
/*   Updated: 2025/11/07 10:25:49 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	select_char(char c)
{
	char	conv_ar[10];
	int		i;

	ft_strlcpy(conv_ar, "cspdiuxX%", 10);
	i = 0;
	while (conv_ar[i])
	{
		if (c == conv_ar[i])
			return (conv_ar[i]);
		i++;
	}
	return (0);
}

static void	select_print(va_list ap, char c, int *len)
{
	if (c == 'c')
		print_char((char)va_arg(ap, int), len);
	else if (c == 's')
		print_str(va_arg(ap, char *), len);
	else if (c == 'd' || c == 'i')
		print_nb(va_arg(ap, int), len);
	else if (c == 'u')
		print_uint(va_arg(ap, unsigned int), len);
	else if (c == 'p')
		print_ptr(va_arg(ap, void *), len);
	else if (c == 'x' || c == 'X')
		print_hex(va_arg(ap, unsigned long), c, len);
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		*len += 1;
	}
}

static void	ft_printf_process(va_list ap, const char *s, int *len)
{
	int		i;
	char	conv_type;

	i = 0;
	while (s[i])
	{
		conv_type = 0;
		if (s[i] == '%')
			conv_type = select_char(s[++i]);
		if (conv_type != 0)
		{
			select_print(ap, conv_type, len);
			i++;
		}
		else if (s[i])
		{
			ft_putchar_fd(s[i], 1);
			*len += 1;
			i++;
		}
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;

	if (!s)
		return (-1);
	va_start(ap, s);
	len = 0;
	ft_printf_process(ap, s, &len);
	va_end(ap);
	return (len);
}
