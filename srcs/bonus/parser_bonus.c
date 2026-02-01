/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:47:02 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/01 10:18:38 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	open_files(t_pipex *data, int ac, char **av, int here_doc)
{
	if (here_doc)
	{
		data->in_fd = open("/tmp/.here_doc_tmp", O_RDONLY);
		unlink("/tmp/.here_doc_tmp");
	}
	else
		data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd == -1)
		perror("Error");
	if (here_doc)
		data->out_fd = open(av[ac - 1], O_APPEND | O_CREAT | O_WRONLY, 0644);
	else
		data->out_fd = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data->out_fd == -1)
		perror("Error"); 
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

static t_list	*build_cmd_list(int ac, char **av, int here_doc)
{
	char	**cmd;
	t_list	*cmd_list;
	int		i;

	cmd_list = NULL;
	i = 2 + here_doc;
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

static int	parse_heredoc(t_pipex *data, char **av)
{
	int	status;

	if (ft_strncmp(av[1], "here_doc", 8) != 0)
	{
		data->delimiter = NULL;
		return (0);
	}
	data->delimiter = ft_strdup(av[2]);
	if (!data->delimiter)
	{
		perror("Error");
		return (-1);
	}
	status = read_h_doc(data);
	if (status == -1)
	{
		unlink("/tmp/.here_doc_tmp");
		free(data->delimiter);
		return (-1);
	}
	free(data->delimiter);
	return (1);
}

t_pipex	parse(int ac, char **av, char **ev)
{
	t_pipex	data;
	int		here_doc;

	data.ev = ev;
	here_doc = parse_heredoc(&data, av);
	if (here_doc == -1)
		exit(EXIT_FAILURE);
	data.cmds = build_cmd_list(ac, av, here_doc);
	if (!data.cmds)
	{
		if (data.delimiter)
			free(data.delimiter);
		ft_puterror(NULL);
	}
	data.cmd_count = count_cmd(data.cmds);
	data.pids = ft_calloc(data.cmd_count, sizeof(pid_t));
	if (!data.pids)
	{
		if (data.delimiter)
			free(data.delimiter);
		free_lst(data.cmds);
		ft_puterror(NULL);
	}
	open_files(&data, ac, av, here_doc);
	data.prev_fd = -1;
	return (data);
}
