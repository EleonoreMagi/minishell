/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:36:05 by dmillan           #+#    #+#             */
/*   Updated: 2022/10/19 21:06:34 by bpoetess         ###   ########.fr       */
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
	t_token	*tmp_next;

	tmp = tokens;
	if (tmp)
		tmp_next = tmp->next;
	while (tmp != NULL)
	{
		if (tmp && tmp->value)
			free(tmp->value);
		if (tmp)
			free (tmp);
		tmp = tmp_next;
		if (tmp)
			tmp_next = tmp->next;
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
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (line[i + 1] != NULL)
		i++;
	while (i >= 0)
	{
		tmp->idx = i;
		ft_token_data_fill(tmp, line, i);
		if (tmp->type == NONE)
			tmp->value = ft_strdup(line[i]);
		if (i > 0)
		{
			token_new = ft_tokens_init();
			tmp->next = token_new;
			tmp = tmp->next;
		}
		i--;
	}
}
