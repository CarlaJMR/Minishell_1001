/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/29 19:14:45 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_type(char *str)
{
	if (str[0] == '>' && !str[1])
		return (1);
	else if (str[0] == '>')
		return (2);
	else if (str[0] == '<' && !str[1])
		return (3);
	else
		return (4);
}

void	infile_error(char **line, int *i)
{
	if (access(line[(*i) + 1], F_OK))
	{
		set_exit_code(1, 1);
		ft_putstr_fd(line[(*i) + 1], 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	else if (access(line[(*i) + 1], R_OK))
	{
		set_exit_code(126, 1);
		ft_putstr_fd(line[(*i) + 1], 1);
		ft_putendl_fd(": Permission denied", 1);
	}
}

void	manage_outfile(int option, char **line, int *i, t_cmd *cm)
{
	if (cm->redir[1] > 2 && (option == 1 || option == 2))
		close(cm->redir[1]);
	if (option == 2)
		cm->redir[1] = open(line[(*i) + 1], \
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (option == 1)
		cm->redir[1] = open(line[(*i) + 1], \
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void	manage_redirections(char **line, int *i, t_cmd *cm, t_data sh)
{
	int	option;
	int	hd;

	option = redir_type(line[*i]);
	if (option == 4)
		hd = ft_here_doc(line[(*i) + 1], sh);
	if (cm->redir[0] != -1)
	{
		if (cm->redir[0] > 2 && (option == 3 || option == 4))
			close(cm->redir[0]);
		if (option == 3)
			cm->redir[0] = open(line[(*i) + 1], O_RDONLY, 0644);
		else if (option == 4)
			cm->redir[0] = hd;
		if (cm->redir[0] < 0)
			infile_error(line, i);
	}
	if (cm->redir[1] != -1)
		manage_outfile(option, line, i, cm);
	(*i)++;
}
