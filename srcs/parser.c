/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:37:17 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/20 16:39:09 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	open_files(t_pipex *data, int ac, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		ft_puterror(NULL);
	data->out_fd = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data->out_fd == -1)
	{
		close(data->in_fd);
		ft_puterror(NULL);
	}
}

static int	add_to_list(t_list **lst, char **content)
{
	t_list	*node;

	if (!lst || !content || !*content)
		return (-1);
	if (!*lst)
	{
		*lst = ft_lstnew((void *)content);
		if (!*lst)
			return (-1);
		return (0);
	}
	node = ft_lstnew((void *)content);
	if (!node)
		return (-1);
	ft_lstadd_back(lst, node);
	return (0);
}

static t_list	*build_cmd_list(int ac, char **av)
{
	char	**cmd;
	t_list	*cmd_list;
	int		i;

	cmd_list = NULL;
	i = 2;
	while (i < ac - 1)
	{
		cmd = ft_split(av[i], ' ');
		if (!cmd || !*cmd)
			return (NULL);
		if (add_to_list(&cmd_list, cmd) == -1)
		{
			ft_freestrar(cmd);
			free_lst(cmd_list);
			return (NULL);
		}
		i++;
	}
	return (cmd_list);
}

static int	count_cmd(t_list *cmds)
{
	t_list	*tmp;
	int		count;

	tmp = cmds;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_pipex	parse(int ac, char **av, char **ev)
{
	t_pipex	data;

	data.ev = ev;
	open_files(&data, ac, av);
	data.cmds = build_cmd_list(ac, av);
	if (!data.cmds)
		ft_puterror(NULL);
	data.cmd_count = count_cmd(data.cmds);
	if (data.cmd_count == 0)
	{
		free_lst(data.cmds);
		ft_puterror("Error : Invalid number of commands\n");
	}
	return (data);
}
