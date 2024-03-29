/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:40:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/20 16:52:46 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redirections_exist(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp->next != NULL)
	{
		if (tmp->type != NONE && tmp->type != PIPE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	ft_pipes_exist(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	ft_redirections_parse(t_token *tokens, t_cmd_list *cmd_list)
{
	int		fd_in;
	int		fd_out;
	int		**fd_list;
	char	**input;
	t_token	*tmp;

	tmp = tokens;
	fd_list = ft_redirect_init(&tmp);
	if (fd_list == NULL)
		return ;
	tmp = tokens;
	fd_in = ft_get_fd_in(fd_list[0]);
	fd_out = ft_get_fd_out(fd_list[1]);
	input = ft_tokens_convert_redirect(tmp);
	if (input != NULL && input[0] != NULL)
		ft_add_cmd(cmd_list, input, fd_in, fd_out);
	ft_free_line(input);
	free(fd_list[0]);
	free(fd_list[1]);
	free(fd_list);
}

t_token	*ft_lexer(char *line)
{
	t_token	*tokens;
	char	**line_split;

	line_split = ft_sp_split(line);
	if (line_split == NULL)
		return (NULL);
	tokens = ft_tokens_init();
	ft_tokens_get(tokens, line_split);
	ft_free_line(line_split);
	return (tokens);
}

void	ft_parser(char *line, t_env_v **env, t_cmd_list *cmd_list)
{
	t_token		*tokens;
	char		**input;

	tokens = NULL;
	input = NULL;
	if (line[0] != '\0' && ft_redirect_check(line) && ft_quotes_check(line))
	{
		tokens = ft_lexer(line);
		ft_quotes_remove(&tokens, env);
		if (ft_pipes_exist(tokens) == TRUE)
			ft_pipe_parse(tokens, cmd_list);
		else if (ft_redirections_exist(tokens) == TRUE)
			ft_redirections_parse(ft_tokens_invert(tokens), cmd_list);
		else
		{
			input = ft_tokens_convert(ft_tokens_invert(tokens));
			if (input != NULL && input[0] != NULL)
				ft_add_cmd(cmd_list, input, 0, 1);
		}
		ft_executer(cmd_list, *env);
		if (input != NULL && input[0] != NULL)
			ft_free_line(input);
	}
}
