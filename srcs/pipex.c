/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:36:48 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/05 13:00:21 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
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
		dup2(data->p_fd[0], STDIN_FILENO);
		close(data->p_fd[0]);
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
	int		perm_error;

	redir_fds(data, i);
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->out_fd != -1)
		close(data->out_fd);
	perm_error = 0;
	path = parse_path(data->ev, ((char **)cmds->content), &perm_error);
	if (!path)
	{
		if (perm_error == 1)
			perror("Error");
		else
			write(2, "Error: command not found\n", 25);
		free_childs(data);
		exit(127);
	}
	execve(path, ((char **)cmds->content), data->ev);
	perror("execve");
	free_childs(data);
	exit(126);
}

static int	pipeline(t_pipex *data, t_list *cmds, int i)
{
	if (data->in_fd == -1 && i == 0)
	{
		close(data->p_fd[1]);
		data->pids[i] = -1;
		return (0);
	}
	else if (data->out_fd == -1 && i > 0)
	{
		close(data->p_fd[0]);
		data->pids[i] = -1;
		return (0);
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		perror("Error");
		return (-1);
	}
	if (data->pids[i] == 0)
		child_process(data, cmds, i);
	if (i > 0)
		close(data->p_fd[0]);
	if (i < data->cmd_count - 1)
		close(data->p_fd[1]);
	return (1);
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
	{
		perror("Error");
		return (-1);
	}
	while (i < data->cmd_count)
	{
		if (pipeline(data, cmds, i) == -1)
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
