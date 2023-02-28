/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:53:22 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/23 19:01:45 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_addchar_safely(t_core *core, char c)
{
	char	*new;

	new = ft_addchar(core->tokenl->data, c);
	if (new == NULL)
		ft_free_all(core);
	return (new);
}
