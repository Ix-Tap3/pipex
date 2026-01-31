/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:31 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/31 12:12:23 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**ev;
	t_list	*cmds;
	int		cmd_count;
	int		p_fd[2];
	pid_t	pids[2];
	int		prev_fd;
	int		in_fd;
	int		out_fd;
}			t_pipex;

int		pipex(t_pipex *data);

/* PARSER */
t_pipex	parse(int ac, char **av, char **ev);
char	*parse_path(char **ev, char **cmd);

/* UTILS functions */
char	*str_catsep(char *s1, char *s2, char sep);
void	ft_puterror(char *error_msg);
void	free_lst(t_list *lst);
void	log_lst(t_list *lst);
int		count_cmd(t_list *cmds);

#endif
