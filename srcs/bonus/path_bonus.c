/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:18:13 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/05 12:47:32 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	is_custom_path(char *path)
{
	int	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	**set_custom_path_ar(char *path)
{
	char	**path_ar;

	path_ar = ft_calloc(2, sizeof(char *));
	if (!path_ar)
		return (NULL);
	path_ar[0] = ft_strdup(path);
	if (!path)
	{
		free(path_ar);
		return (NULL);
	}
	path_ar[1] = NULL;
	return (path_ar);
}

static char	**set_path_ar(char **ev, char **cmd)
{
	char	**path_ar;
	char	*path_line;
	int		i;

	if (!ev)
		return (NULL);
	if (is_custom_path(cmd[0]))
	{
		path_ar = set_custom_path_ar(cmd[0]);
		return (path_ar);
	}
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

static char	*check_cmd_path(char **path_ar, char **cmd, int *perm_error)
{
	char	*path;
	int		i;

	i = 0;
	while (path_ar[i])
	{
		if (is_custom_path(cmd[0]))
			path = ft_strdup(path_ar[i]);
		else
			path = str_catsep(path_ar[i], cmd[0], '/');
		if (!path)
		{
			ft_freestrar(path_ar);
			return (NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		if (access(path, X_OK) == -1)
			*perm_error = 1;
		free(path);
		i++;
	}
	return (NULL);
}

char	*parse_path(char **ev, char **cmd, int *perm_error)
{
	char	**path_ar;
	char	*path;

	if (ft_isempty(cmd[0]))
		return (NULL);
	path_ar = set_path_ar(ev, cmd);
	if (!path_ar)
		return (NULL);
	path = check_cmd_path(path_ar, cmd, perm_error);
	ft_freestrar(path_ar);
	return (path);
}
