/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:51:02 by pcaplat           #+#    #+#             */
/*   Updated: 2025/10/22 19:04:34 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (!dest && src && size == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	if (size == 0 || size <= dest_len)
		return (size + src_len);
	while (src[i] && dest_len + 1 < size)
		dest[dest_len++] = src[i++];
	dest[dest_len] = '\0';
	return (ft_strlen(dest) + src_len - i);
}
