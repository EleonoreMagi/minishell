/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:36:05 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/17 23:10:36 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_tokens_init(void)
{
	t_token	*token_new;

	token_new = (t_token *)malloc(sizeof(t_token));
	token_new->idx = 0;
	token_new->value = NULL;
	token_new->next = NULL;
	token_new->type = NONE;
	return (token_new);
}

void	ft_token_add(t_token **tokens, t_token *token_to_add)
{
	t_token	*token_new;

	token_new = (t_token *)malloc(sizeof(t_token));
	token_new->idx = token_to_add->idx;
	token_new->value = token_to_add->value;
	token_new->type = token_to_add->type;
	token_new->next = *tokens;
	*tokens = token_new;
}

void	ft_tokens_free(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	ft_token_data_fill(t_token *tokens, char **line, int i)
{
	if (ft_strcmp(line[i], "|") == 0)
	{
		tokens->type = PIPE;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], "<") == 0)
	{
		tokens->type = INPUT;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], ">") == 0)
	{
		tokens->type = TRUNC;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], ">>") == 0)
	{
		tokens->type = APPEND;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], "<<") == 0)
	{
		tokens->type = HEREDOC;
		tokens->value = ft_strdup(line[i]);
	}
}

void	ft_tokens_get(t_token *tokens, char **line)
{
	t_token	*token_new;
	int		i;

	i = 0;
	while (line[i + 1] != NULL)
		i++;
	while (i >= 0)
	{
		tokens->idx = i;
		ft_token_data_fill(tokens, line, i);
		if (tokens->type == NONE)
			tokens->value = ft_strdup(line[i]);
		if (i  > 0)
		{
			token_new = ft_tokens_init();
			tokens->next = token_new;
			tokens = tokens->next;
		}
		i--;
	}
}
