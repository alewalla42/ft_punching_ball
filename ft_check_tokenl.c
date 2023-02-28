/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokenl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:26:43 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:43:58 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_file_data(t_tok *tokenl)
{
	t_tok	*tmp;

	if (tokenl->next_link->type == WORD)
	{
		if (tokenl->data == NULL)
		{
			tokenl->data = ft_strdup(tokenl->next_link->data);
			free(tokenl->next_link->data);
		}
		tmp = tokenl->next_link->next_link;
		free(tokenl->next_link);
		tokenl->next_link = tmp;
	}
}

int	ft_check_double_redirection(t_tok *tokenl, t_tok *tmp)
{
	if (tokenl->data != NULL)
		free(tokenl->data);
	if (tokenl->type == INFILE)
		tokenl->type = HEREDOC;
	if (tokenl->type == OUTFILE)
		tokenl->type = APPEND;
	tmp = tokenl->next_link->next_link;
	free(tokenl->next_link);
	tokenl->next_link = tmp;
	if (tokenl->next_link == NULL)
		return (ft_print_error
			("syntax error near unexpected token `newline'"));
	if (tokenl->next_link->type != WORD)
		return (ft_print_error("minishell: unexpected token `newline'"));
	if (tokenl->type == APPEND || tokenl->type == HEREDOC)
	{
		if (tokenl->next_link->type == WORD)
			ft_get_file_data(tokenl);
	}
	return (0);
}

int	ft_check_pipe(t_tok	*tokenl)
{
	if (tokenl->next_link == NULL || tokenl->previous_link == NULL
		|| tokenl->next_link->type == PIPE
		|| tokenl->previous_link->type == PIPE)
	{
		ft_put_error("minishell: syntax error near unexpected token `|`");
		return (1);
	}
	return (0);
}

int	ft_check_redirection(t_tok *tokenl, t_tok *tmp)
{
	if (tokenl->next_link == NULL)
		return (ft_print_error
			("syntax error near unexpected token `newline'"));
	if (tokenl->type == tokenl->next_link->type)
	{
		if (ft_check_double_redirection(tokenl, tmp) == 1)
			return (1);
	}
	else if (tokenl->next_link->type == WORD)
		ft_get_file_data(tokenl);
	else
		return (ft_print_error
			("minishell: syntax error near unexpected token `newline'"));
	return (0);
}

int	ft_check_tokenl(t_tok *tokenl)
{
	t_tok	*tmp;

	tmp = NULL;
	if (tokenl->type == INFILE || tokenl->type == OUTFILE)
	{
		if (ft_check_redirection(tokenl, tmp) == 1)
			return (1);
	}
	if (tokenl->type == PIPE)
		if (ft_check_pipe(tokenl) == 1)
			return (1);
	if (tokenl->type == WORD)
		if (tokenl->data == NULL)
			return (1);
	if (tokenl->next_link != NULL)
		return (ft_check_tokenl(tokenl->next_link));
	return (0);
}
