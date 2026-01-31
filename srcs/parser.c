/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:37:17 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/31 19:12:57 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	open_files(t_pipex *data, int ac, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
	{
		free_lst(data->cmds);
		ft_puterror(NULL);
	}
	data->out_fd = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data->out_fd == -1)
	{
		free_lst(data->cmds);
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

static char	**set_cmd(char *str)
{
	char	**cmd;

	if (ft_isempty(str))
	{
		cmd = ft_calloc(2, sizeof(char *));
		if (!cmd)
			return (NULL);
		cmd[0] = str;
		cmd[1] = NULL;
	}
	else
		cmd = ft_split(str, ' ');
	return (cmd);
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
		cmd = set_cmd(av[i]);
		if (!cmd || !*cmd)
		{
			free_lst(cmd_list);
			return (NULL);
		}
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

t_pipex	parse(int ac, char **av, char **ev)
{
	t_pipex	data;

	data.ev = ev;
	data.cmds = build_cmd_list(ac, av);
	if (!data.cmds)
		ft_puterror(NULL);
	data.cmd_count = count_cmd(data.cmds);
	if (data.cmd_count == 0)
	{
		free_lst(data.cmds);
		ft_puterror("Error : Invalid number of commands\n");
	}
	open_files(&data, ac, av);
	return (data);
}
