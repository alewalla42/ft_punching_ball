/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:35:10 by alewalla          #+#    #+#             */
/*   Updated: 2023/01/16 18:09:59 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_tok *tokenl, t_env *envl)
{
	if (tokenl->status != 1 && tokenl->type == WORD && tokenl->data != NULL)
		tokenl->data = ft_replace_dollar(tokenl->data, envl);
	if (tokenl->next_link != NULL)
		ft_expand(tokenl->next_link, envl);
}
