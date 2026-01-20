/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:17:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/08 11:12:54 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char sep)
{
	int	i;
	int	nb_words;

	nb_words = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] && s[i] != sep)
			i++;
		nb_words++;
	}
	return (nb_words);
}

char	**set_ar(char **ar, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && ar != NULL)
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		len = ft_strlen_sep(&s[i], c);
		ar[j] = ft_strndup(&s[i], len);
		if (ar[j] == NULL)
		{
			ft_freestrar(ar);
			return (NULL);
		}
		i += len;
		j++;
	}
	ar[j] = NULL;
	return (ar);
}

char	**ft_split(char const *s, char c)
{
	char	**ar;

	ar = ft_calloc((ft_countwords(s, c) + 1), sizeof(char *));
	if (!ar || !s)
	{
		free(ar);
		return (NULL);
	}
	ar = set_ar(ar, s, c);
	if (ar == NULL)
		return (NULL);
	return (ar);
}
