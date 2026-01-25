/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 10:06:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/24 12:06:10 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	write_h_doc(int fd, char *line)
{
	int	i;
	int	status;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		status = write(fd, &line[i], 1);
		if (status == -1)
			break ;
		i++;
	}
	if (line[i] == '\n')
		status = write(fd, &line[i], 1);
	if (status == -1)
	{
		perror("write");
		close(fd);
		unlink("/tmp/.here_doc_tmp");

	}
	return (status);
}

int	read_h_doc(t_pipex *data)
{
	int		fd;
	int		d_len;
	char	*line;

	fd = open("/tmp/.here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	d_len = ft_strlen(data->delimiter);
	line = get_next_line(0, data->delimiter);
	while (line)
	{
		if (ft_strncmp(data->delimiter, line, d_len) == 0)
			break ;
		if (write_h_doc(fd, line) == -1)
			return (-1);
		free(line);
		line = get_next_line(0, data->delimiter);
	}
	free(line);
	close(fd);
	return (1);
}
