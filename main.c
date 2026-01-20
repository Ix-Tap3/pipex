/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:10:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/20 17:26:46 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	close_all(t_pipex *data)
{
	close(data->in_fd);
	close(data->out_fd);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
}

int	main(int ac, char **av, char **ev)
{
	t_pipex	data;
	
	if (ac < 5)
	{
		ft_puterror("Error : Invalid number of arguments.\n");
		return (1);
	}
	data = parse(ac, av, ev);
	if (pipex(&data) == -1)
	{
		close_all(&data);
		free_lst(data.cmds);
		ft_puterror(NULL);
		return (1);
	}
	close_all(&data);
	free_lst(data.cmds);
	return (0);
}
