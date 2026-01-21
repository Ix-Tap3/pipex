/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:36:48 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/21 17:48:36 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	close_fds(t_pipex *data)
{
	close(data->in_fd);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
	close(data->out_fd);
}

static void	wait_all(t_pipex *data, int *status)
{
	close_fds(data);
	waitpid(data->pids[0], status, 0);
	waitpid(data->pids[1], status, 0);
}

static int	child_process(t_pipex *data, t_list *cmds, int i)
{
	char	*path;

	if (i == 0)
		dup2(data->in_fd, STDIN_FILENO);
	else
		dup2(data->p_fd[0], STDIN_FILENO);
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
	int		status;

	cmds = data->cmds;
	status = 0;
	i = 0;
	if (pipe(data->p_fd) == -1)
		return (-1);
	while (i < data->cmd_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (-1);
		if (data->pids[i] == 0)
		{
			if (child_process(data, cmds, i) == -1)
				return (-1);
		}
		cmds = cmds->next;
		i++;
	}
		wait_all(data, &status);
		return (1);
}
