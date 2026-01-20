/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:27:05 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/21 13:59:38 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*des;
	unsigned char	*sr;

	des = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (des > sr && des < (sr + n))
	{
		while (n--)
			des[n] = sr[n];
	}
	else
	{
		while (n--)
			*des++ = *sr++;
	}
	return (dest);
}
