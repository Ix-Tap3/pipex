/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:10:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/21 21:50:40 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

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
		free_lst(data.cmds);
		free(data.pids);
		ft_puterror(NULL);
		return (1);
	}
	free_lst(data.cmds);
	free(data.pids);
	return (0);
}
