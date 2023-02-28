/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_first_block.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:32:25 by alewalla          #+#    #+#             */
/*   Updated: 2023/01/19 18:06:58 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_status(char c)
{
	if (c == '"')
		return (IN_DOUBLE);
	else if (c == '\'')
		return (IN_SINGLE);
	else
		return (OUT);
}

int	ft_set_type(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INFILE);
	else if (c == '>')
		return (OUTFILE);
	else
		return (WORD);
}

void	ft_setup_first_block(t_tok *tokenl)
{
	tokenl->status = OUT;
	tokenl->type = -1;
	tokenl->data = NULL;
	tokenl->merge = 0;
	tokenl->next_link = NULL;
	tokenl->previous_link = NULL;
}
