/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 00:49:31 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 22:40:38 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_fd(int og_fd, char *operator)
{
	if (ft_strcmp(operator, "<") == 0)
		dup2(STDIN_FILENO, og_fd);
	else if (ft_strcmp(operator, ">") == 0 || ft_strcmp(operator, ">>") == 0)
		dup2(STDOUT_FILENO, og_fd);
}

static int	ft_return_fd_input(char *filename, int fd)
{
	fd = access(filename, F_OK);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "No such file or directory");
		return (-1);
	}
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "Permission denied");
		return (-1);
	}
	return (fd);
}

static int	ft_return_fd_output(char *filename, int fd)
{
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_exit_with_error(filename, "Permission denied");
		return (-1);
	}
	return (fd);
}

int	ft_redirect(char *filename, int type)
{
	int	fd;

	fd = 0;
	if (type == INPUT || type == HEREDOC)
		return (ft_return_fd_input(filename, fd));
	else if (type == TRUNC)
		return (ft_return_fd_output(filename, fd));
	else if (type == APPEND)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_exit_with_error(filename, "Permission denied");
			return (-1);
		}
		return (fd);
	}
	return (-1);
}
