/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:18:27 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/01 11:52:27 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"
#include <unistd.h>

static int	wait_all(t_pipex *data)
{
	int	i;
	int	status;
	int	final_status;

	status = 0;
	final_status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		if (data->pids[i] != -1)
			waitpid(data->pids[i], &status, 0);
		if (i == data->cmd_count - 1)
			final_status = (status >> 8) & 0xFF;
		i++;
	}
	return (final_status);
}

static void	redir_fds(t_pipex *data, int i)
{
	if (i == 0)
		dup2(data->in_fd, STDIN_FILENO);
	else
	{
		dup2(data->prev_fd, STDIN_FILENO);
		if (data->prev_fd != -1)
			close(data->prev_fd);
	}
	if (i == data->cmd_count - 1)
		dup2(data->out_fd, STDOUT_FILENO);
	else
	{
		dup2(data->p_fd[1], STDOUT_FILENO);
		close(data->p_fd[1]);
		close(data->p_fd[0]);
	}
}

static void	child_process(t_pipex *data, t_list *cmds, int i)
{
	char	*path;

	redir_fds(data, i);
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->out_fd != -1)
		close(data->out_fd);
	path = parse_path(data->ev, ((char **)cmds->content));
	if (!path)
	{
		if (i != data->cmd_count - 1 || data->out_fd != -1)
			write(2, "Error: command not found\n", 25);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_lst(data->cmds);
		free(data->pids);
		exit(127);
	}
	if (i == data->cmd_count - 1 && data->out_fd == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_lst(data->cmds);
		free(data->pids);
		free(path);
		exit(126);
	}
	execve(path, ((char **)cmds->content), data->ev);
	perror("execve");
	free_lst(data->cmds);
	free(path);
	free(data->pids);
	exit(126);
}

static int	pipeline(t_pipex *data, t_list *cmds, int i)
{
	if (data->in_fd == -1 && i == 0)
	{
		if (i < data->cmd_count - 1)
		{
			if (pipe(data->p_fd) == -1)
			{
				perror("Error");
				return (-1);
			}
			close(data->p_fd[1]);
			data->prev_fd = data->p_fd[0];
		}
		data->pids[i] = -1;
		return (0);
	}
	if (i < data->cmd_count - 1)
	{
		if (pipe(data->p_fd) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		if (i < data->cmd_count - 1)
		{
			close(data->p_fd[0]);
			close(data->p_fd[1]);
		}
		return (-2);
	}
	if (data->pids[i] == 0)
		child_process(data, cmds, i);
	if (i > 0 && data->prev_fd != -1)
		close(data->prev_fd);
	if (i < data->cmd_count - 1)
	{
		data->prev_fd = data->p_fd[0];
		close(data->p_fd[1]);
	}
	return (1);
}

int	pipex(t_pipex *data)
{
	t_list	*cmds;
	int		i;
	int		status;
	int		ret;

	cmds = data->cmds;
	i = 0;
	status = 0;
	ret = 0;
	while (i < data->cmd_count)
	{
		ret = pipeline(data, cmds, i);
		if (ret == -2)
			perror("Error");
		if (ret < 0)
			break ;
		cmds = cmds->next;
		i++;
	}
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->out_fd != -1)
		close(data->out_fd);
	status = wait_all(data);
	return (status);
}
