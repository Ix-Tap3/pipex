/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:18:27 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/21 22:04:08 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	close_fds(t_pipex *data)
{
	close(data->in_fd);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
	close(data->out_fd);
	if (data->prev_fd != -1)
		close(data->prev_fd);
}

static void	wait_all(t_pipex *data)
{
	int	i;
	int	status;

	close_fds(data);
	status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pids[0], &status, 0);
		i++;
	}
}

static int	child_process(t_pipex *data, t_list *cmds, int i)
{
	char	*path;

	if (i == 0)
		dup2(data->in_fd, STDIN_FILENO);
	else
		dup2(data->prev_fd, STDIN_FILENO);
	if (i == data->cmd_count - 1)
		dup2(data->out_fd, STDOUT_FILENO);
	else
		dup2(data->p_fd[1], STDOUT_FILENO);
	close_fds(data);
	path = parse_path(data->ev, ((char **)cmds->content));
	if (!path)
		return (-1);
	execve(path, ((char **)cmds->content), data->ev);
	return (-1);
}

int	pipex(t_pipex *data)
{
	t_list	*cmds;
	int		i;

	cmds = data->cmds;
	i = 0;
	while (i < data->cmd_count)
	{
		if (i < data->cmd_count - 1)
		{
			if (pipe(data->p_fd) == -1)
				return (-1);
		}
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (-1);
		if (data->pids[i] == 0)
		{
			if (child_process(data, cmds, i) == -1)
				return (-1);
		}
		if (i > 0)
			close(data->prev_fd);
		if (i < data->cmd_count - 1)
		{
			data->prev_fd = data->p_fd[0];
			close(data->p_fd[1]);
		}
		cmds = cmds->next;
		i++;
	}
	wait_all(data);
	return (1);
}
