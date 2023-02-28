/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:20:08 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/26 20:07:15 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_status(int status, t_tok *tokenl)
{
	if (tokenl->status == status)
		ft_create_empty_block_to_merge(tokenl);
	if (tokenl->status == OUT)
	{
		if (tokenl->data == NULL)
		{
			tokenl->status = status;
			tokenl->type = WORD;
		}
		else
			ft_create_quote_block(status, tokenl);
	}
}

void	ft_check_whitespace(char *cmd_line, t_tok *tokenl, int *i)
{
	if (tokenl->previous_link && tokenl->previous_link->merge)
				tokenl->previous_link->merge = 0;
	while (ft_isspace(cmd_line[(*i)]))
		(*i)++;
	(*i)--;
	if (tokenl->type != -1)
		ft_create_empty_block(tokenl);
}

void	ft_add_to_tokenl(char *cmd_line, t_tok *tokenl, int *i)
{
	if ((cmd_line[(*i)] == ' '
			|| cmd_line[(*i)] == '\t') && tokenl->status == OUT)
		ft_check_whitespace(cmd_line, tokenl, i);
	else if (cmd_line[(*i)] == '"' && tokenl->status != IN_SINGLE)
		ft_update_status(IN_DOUBLE, tokenl);
	else if (cmd_line[(*i)] == '\'' && tokenl->status != IN_DOUBLE)
		ft_update_status(IN_SINGLE, tokenl);
	else if (tokenl->status == IN_DOUBLE || tokenl->status == IN_SINGLE)
		tokenl->data = ft_addchar(tokenl->data, cmd_line[(*i)]);
	else if (cmd_line[(*i)] == '|')
		ft_create_type_block(tokenl, PIPE);
	else if (cmd_line[(*i)] == '<')
		ft_create_type_block(tokenl, INFILE);
	else if (cmd_line[(*i)] == '>')
		ft_create_type_block(tokenl, OUTFILE);
	else if (tokenl->type == WORD)
		tokenl->data = ft_addchar(tokenl->data, cmd_line[(*i)]);
	else if (tokenl->type == -1)
	{
		tokenl->type = WORD;
		tokenl->data = ft_addchar(tokenl->data, cmd_line[(*i)]);
	}
	else
		ft_create_word_block(tokenl, cmd_line[(*i)]);
}

void	ft_parsing(char *cmd_line, t_tok *tokenl)
{
	int	i;

	i = 0;
	ft_setup_first_block(tokenl);
	while (ft_isspace(cmd_line[i]))
		i++;
	while (cmd_line[i])
	{
		ft_add_to_tokenl(cmd_line, tokenl, &i);
		while (tokenl->next_link != NULL)
			tokenl = tokenl->next_link;
		i++;
	}
	if (tokenl->type == -1)
	{
		if (tokenl->previous_link != NULL)
		{
			tokenl->previous_link->next_link = NULL;
			free(tokenl);
		}
	}
}
