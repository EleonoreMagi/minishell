/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchbinarypath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:37:48 by bpoetess          #+#    #+#             */
/*   Updated: 2022/09/07 21:24:51 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**getbinarypaths(char *env_paths)
{
	char	**paths;

	if (env_paths)
	{
		paths = ft_split(env_paths, ':');
		return (paths);
	}
	paths = (char **) malloc (sizeof (char *) * 2);
	paths [0] = ft_strdup(".");
	paths [1] = 0;
	return (paths);
}

static char	*choosebinarypath(char **oldfullpath, char *newpath, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(ft_strdup(newpath), "/");
	if (!tmp)
		return (0);
	res = ft_strjoin(tmp, cmd);
	if (access(res, F_OK) != -1)
	{
		if (oldfullpath)
			free (*oldfullpath);
		if (oldfullpath)
			*oldfullpath = 0;
		return (res);
	}
	else
		free (res);
	return (0);
}

static char	*checkbinarypaths(char *cmd, char **paths)
{
	char	*res;
	int		i;

	i = 0;
	res = 0;
	while (paths && paths[i])
	{
		res = choosebinarypath(&res, paths[i], cmd);
		if (access(res, X_OK) != -1)
			return (res);
		i++;
	}
	return (res);
}

char	*searchbinarypath(char *cmd, t_env_v *env_list)
{
	char	**paths;
	char	*res;
	int		i;

	paths = getbinarypaths(ft_env_get_value(env_list, "PATH"));
	if (!paths)
		return (0);
	res = checkbinarypaths(cmd, paths);
	i = 0;
	(void) i;
	while (paths[i])
		free (paths[i++]);
	free (paths);
	return (res);
}
