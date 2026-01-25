/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:42:08 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/24 11:25:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**ev;
	char	*delimiter;
	t_list	*cmds;
	pid_t	*pids;
	int		p_fd[2];
	int		cmd_count;
	int		prev_fd;
	int		in_fd;
	int		out_fd;
}			t_pipex;

int		pipex(t_pipex *data);

/* PARSER */
t_pipex	parse(int ac, char **av, char **ev);
char	*parse_path(char **ev, char **cmd);
int		read_h_doc(t_pipex *data);

/* UTILS functions */
char	*str_catsep(char *s1, char *s2, char sep);
void	ft_puterror(char *error_msg);
void	free_lst(t_list *lst);
void	log_lst(t_list *lst);
int		count_cmd(t_list *lst);

#endif
