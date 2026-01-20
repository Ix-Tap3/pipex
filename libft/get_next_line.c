/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:39:50 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/08 11:13:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_gnl_buffer(char *gnl_buffer, char *buff)
{
	int		len;
	int		i;
	int		j;
	char	*new_buff;

	len = ft_strlen_sep(gnl_buffer, '\0') + ft_strlen_sep(buff, '\0');
	new_buff = ft_gnlcalloc((len + 1), sizeof(char));
	if (!new_buff)
		return (NULL);
	i = 0;
	while (gnl_buffer && gnl_buffer[i])
	{
		new_buff[i] = gnl_buffer[i];
		i++;
	}
	j = 0;
	while (buff[j])
		new_buff[i++] = buff[j++];
	new_buff[i] = '\0';
	free(gnl_buffer);
	return (new_buff);
}

char	*set_substr(const char *s, int len)
{
	char	*sub;
	int		i;

	sub = ft_gnlcalloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[i])
	{
		sub[i] = s[i];
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static int	read_line(int fd, char **gnl_buffer)
{
	int		rd_state;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	rd_state = 1;
	while (rd_state > 0 && !ft_isinstr(*gnl_buffer, '\n'))
	{
		rd_state = read(fd, buff, BUFFER_SIZE);
		if (rd_state < 0)
		{
			free(buff);
			free(*gnl_buffer);
			*gnl_buffer = NULL;
			return (-1);
		}
		if (rd_state == 0)
			break ;
		buff[rd_state] = '\0';
		*gnl_buffer = fill_gnl_buffer(*gnl_buffer, buff);
	}
	free(buff);
	return (rd_state);
}

char	*get_next_line(int fd)
{
	static char	*gnl_buffer[1024];
	char		*line;
	int			rd_state;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	rd_state = read_line(fd, &gnl_buffer[fd]);
	if (rd_state < 0)
		return (NULL);
	if (gnl_buffer[fd] && !gnl_buffer[fd][0] && rd_state == 0)
	{
		free(gnl_buffer[fd]);
		gnl_buffer[fd] = NULL;
		return (NULL);
	}
	else if (gnl_buffer[fd] && gnl_buffer[fd][0] && rd_state == 0)
	{
		line = ft_gnlsubstr(&gnl_buffer[fd]);
		free(gnl_buffer[fd]);
		gnl_buffer[fd] = NULL;
		return (line);
	}
	line = ft_gnlsubstr(&gnl_buffer[fd]);
	return (line);
}
