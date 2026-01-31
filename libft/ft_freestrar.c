/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:50:50 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/31 11:23:43 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freestrar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i] != NULL)
	{
		if (ar[i] && !ft_isempty(ar[i]))
			free(ar[i]);
		i++;
	}
	free(ar);
}
