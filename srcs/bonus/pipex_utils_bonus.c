/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:24:59 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/01 18:36:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	free_childs(t_pipex *data)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_lst(data->cmds);
	free(data->pids);
}

int	check_in_fd(t_pipex *data, int i)
{
	if (data->in_fd == -1 && i == 0)
	{
		if (i < data->cmd_count - 1)
		{
			close(data->p_fd[1]);
			data->prev_fd = data->p_fd[0];
		}
		data->pids[i] = -1;
		return (-1);
	}
	return (0);
}

void	close_pfd(t_pipex *data)
{
	close(data->p_fd[0]);
	close(data->p_fd[1]);
}
