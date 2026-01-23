/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:36:48 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/23 15:32:13 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	wait_all(t_pipex *data)
{
	int	i;
	int	status;
	int	final_status;

	status = 0;
	final_status = 0;
	i = 0;
	while (i < data->cmd_count - 1)
	{
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

	redir_fds(data, i);
	close(data->in_fd);
	close(data->out_fd);
	path = parse_path(data->ev, ((char **)cmds->content));
	if (!path)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		free_lst(data->cmds);
		exit(127);
	}
	execve(path, ((char **)cmds->content), data->ev);
	perror("execve");
	free_lst(data->cmds);
	exit(126);
}

static int	pipeline(t_pipex *data, t_list *cmds, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		perror("fork");
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
		perror("pipe");
		return (-1);
	}
	while (i < data->cmd_count)
	{
		if (pipeline(data, cmds, i) == -1)
			break ;
		cmds = cmds->next;
		i++;
	}
	close(data->in_fd);
	close(data->out_fd);
	status = wait_all(data);
	return (status);
}
