/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 23:08:46 by dmillan           #+#    #+#             */
/*   Updated: 2022/08/10 00:30:45 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	free_arg(char **args, t_env_v *env_v)
{
	int	i;
	int	atoi;

	ft_env_free(&env_v);
	i = 0;
	atoi = 0;
	if (args != NULL && args[1] != NULL)
		atoi = ft_atoi(args[1]);
	while (args != NULL && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (atoi);
}

void	ft_exit(char **args, int ctrl_d, t_env_v *env_v)
{
	if (ctrl_d == TRUE)
	{
		rl_replace_line("", 0);
		printf("\33[1A");
		rl_on_new_line();
		rl_redisplay();
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	if (args != NULL && args[1] != NULL)
	{
		if (ft_isdigit(args[1][0]) == FALSE)
			ft_exit_with_error("exit", "numeric argument required");
		else if (args[2] != NULL)
		{
			ft_exit_with_error("exit", "too many arguments");
			return ;
		}
		exit(free_arg(args, env_v));
	}
	exit(free_arg(args, env_v));
}
