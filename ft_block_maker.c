/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block_maker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:57:19 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/25 20:26:55 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_empty_block_to_merge(t_tok *tokenl)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		ft_free_all_before_exec();
	new->data = NULL;
	new->type = -1;
	new->status = OUT;
	new->merge = 1;
	new->previous_link = tokenl;
	new->next_link = NULL;
	tokenl->next_link = new;
	tokenl->merge = 1;
}

void	ft_create_empty_block(t_tok *tokenl)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		ft_free_all_before_exec();
	new->data = NULL;
	new->type = -1;
	new->status = OUT;
	new->merge = 1;
	new->previous_link = tokenl;
	new->next_link = NULL;
	tokenl->next_link = new;
	tokenl->merge = 0;
}

void	ft_create_type_block(t_tok *token, int type)
{
	t_tok	*new;

	if (token->type == -1)
		new = token;
	else
	{
		new = malloc(sizeof(t_tok));
		if (new == NULL)
			ft_free_all_before_exec();
		token->next_link = new;
	}
	if (token->type != -1)
		new->previous_link = token;
	new->data = NULL;
	new->type = type;
	new->status = OUT;
	new->merge = 0;
	new->next_link = NULL;
	ft_create_empty_block(new);
}

void	ft_create_word_block(t_tok *tokenl, char data)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		ft_free_all_before_exec();
	new->data = ft_addchar(new->data, data);
	new->type = WORD;
	new->status = OUT;
	new->merge = 1;
	new->previous_link = tokenl;
	new->next_link = NULL;
	tokenl->next_link = new;
}

void	ft_create_quote_block(int status, t_tok *tokenl)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		ft_free_all_before_exec();
	new->data = NULL;
	new->type = WORD;
	new->status = status;
	new->merge = 1;
	new->previous_link = tokenl;
	new->next_link = NULL;
	tokenl->next_link = new;
	tokenl->merge = 1;
}
