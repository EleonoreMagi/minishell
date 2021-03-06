/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:22:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/15 03:27:53 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_home(t_env_v	**env)
{
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = ft_env_get_value(*env, "HOME");
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
		pwd = ft_append("~", pwd + ft_strlen(home));
	free(home);
	pwd = ft_append(BLUE, pwd);
	pwd = ft_append(pwd, " ");
	pwd = ft_append(" ", pwd);
	pwd = ft_append(pwd, RESETCOLOR);
	return (pwd);
}

static char	*ft_get_user(t_env_v	**env)
{
	char	*user;

	user = NULL;
	user = ft_env_get_value(*env, "USER");
	if (!user)
		user = ft_strjoin(NULL, "guest");
	user = ft_append(BLUE, user);
	return (user);
}

char	*ft_get_prompt(t_env_v	**env)
{
	char	*user;
	char	*home;
	char	*prompt_full;

	user = ft_get_user(env);
	prompt_full = ft_append(user, "@minishell");
	free(user);
	home = ft_get_home(env);
	prompt_full = ft_append(prompt_full, home);
	free(home);
	if (!g_status || g_status == -1)
		prompt_full = ft_append(prompt_full, BLUE);
	else
		prompt_full = ft_append(prompt_full, RED);
	prompt_full = ft_append(prompt_full, "$ ");
	prompt_full = ft_append(prompt_full, RESETCOLOR);
	return (prompt_full);
}
