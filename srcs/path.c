/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 08:21:54 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/31 11:19:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**set_path_ar(char **ev)
{
	char	**path_ar;
	char	*path_line;
	int		i;

	if (!ev)
		return (NULL);
	i = 0;
	while (ev[i])
	{
		path_line = ft_strnstr(ev[i], "PATH=", 5);
		if (path_line)
			break ;
		i++;
	}
	if (!path_line)
		return (NULL);
	path_ar = ft_split(&path_line[5], ':');
	return (path_ar);
}

static char	*check_cmd_path(char **path_ar, char **cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (path_ar[i])
	{
		path = str_catsep(path_ar[i], cmd[0], '/');
		if (!path)
		{
			free(path);
			return (NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*parse_path(char **ev, char **cmd)
{
	char	**path_ar;
	char	*path;

	if (ft_isempty(cmd[0]))
		return (NULL);
	path_ar = set_path_ar(ev);
	if (!path_ar)
		return (NULL);
	path = check_cmd_path(path_ar, cmd);
	ft_freestrar(path_ar);
	return (path);
}
