/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenl_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:12:34 by alewalla          #+#    #+#             */
/*   Updated: 2023/01/19 18:07:19 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokenl(t_tok *tokenl)
{
	t_tok	*tmp;

	while (tokenl)
	{
		tmp = tokenl->next_link;
		free(tokenl);
		tokenl = tmp;
	}
}

void	ft_clean_tokenl(t_tok *tokenl)
{
	t_tok	*tmp;	

	tmp = NULL;
	if (tokenl->data != NULL)
		free(tokenl->data);
	if (tokenl->next_link != NULL)
		tmp = tokenl->next_link;
	tokenl->next_link = NULL;
	if (tmp != NULL)
		ft_clean_tokenl(tmp);
	free(tmp);
}
