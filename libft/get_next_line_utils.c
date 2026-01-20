/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:44:54 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/20 10:19:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_sep(const char *s, char sep)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] && s[len] != sep)
		len++;
	return (len);
}

int	ft_isinstr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_gnlcalloc(size_t n, size_t size)
{
	char	*tmp;
	size_t	i;

	if (n == 0)
	{
		tmp = malloc(1);
		if (tmp == NULL)
			return (NULL);
		return (tmp);
	}
	if (n > (size_t)-1 / size)
		return (NULL);
	tmp = malloc(n * size);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < n)
		tmp[i++] = 0;
	return (tmp);
}

char	*ft_strfdup(char *s, int index)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen_sep(&s[index], '\0');
	tmp = ft_gnlcalloc((len + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[index + i])
	{
		tmp[i] = s[index + i];
		i++;
	}
	free(s);
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_gnlsubstr(char **s)
{
	char	*sub;
	int		len;

	if (!(*s))
		return (NULL);
	len = ft_strlen_sep(*s, '\n');
	if (ft_isinstr(*s, '\n'))
		len++;
	sub = set_substr(*s, len);
	if (!sub)
		return (NULL);
	if (ft_isinstr(*s, '\n'))
		*s = ft_strfdup(*s, len);
	else
		*s = ft_strfdup(*s, 0);
	if (!s)
		return (NULL);
	return (sub);
}
