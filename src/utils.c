/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:14:08 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/17 23:53:53 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_fd_in(int *fd_list)
{
	int	i;

	i = 0;
	{
		while (fd_list[i] != -1)
		{
			if (fd_list[i + 1] == -1)
				return (fd_list[i]);
			close(fd_list[i]);
			i++;
		}
	}
	return (0);
}

int	ft_get_fd_out(int *fd_list)
{
	int	i;

	i = 0;
	while (fd_list[i] != -1)
	{
		if (fd_list[i + 1] == -1)
			return (fd_list[i]);
		close(fd_list[i]);
		i++;
	}
	return (1);
}

int	ft_count_env(t_env_v	*tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_collect_envp(t_env_v **env)
{
	t_env_v	*tmp;
	int		count;
	int		i;
	char	**envp;

	tmp = *env;
	count = ft_count_env(tmp);
	envp = (char **)malloc(count * sizeof(char *));
	i = 0;
	tmp = *env;
	while (tmp != NULL)
	{
		envp[i] = ft_strdup(tmp->name);
		envp[i] = ft_strjoin(envp[i], "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (envp);
}
