/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:10:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/31 11:51:54 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int ac, char **av, char **ev)
{
	t_pipex	data;

	if (ac != 5)
	{
		ft_puterror("Error : Invalid number of arguments.\n");
		return (1);
	}
	data = parse(ac, av, ev);
	pipex(&data);
	free_lst(data.cmds);
	return (0);
}
