/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envl_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:41:56 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/26 20:51:38 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_value(t_env	*envl, char *name, char *value)
{
	t_env	*tmp;
	char	*buff;

	tmp = envl->next_link;
	while (tmp->next_link != NULL && (ft_strcmp(tmp->name, name) != 0))
		tmp = tmp->next_link;
	buff = ft_strjoin(tmp->value, value);
	free(tmp->value);
	tmp->value = buff;
}

int	ft_is_in_envl(t_env *envl, char *name)
{
	t_env	*tmp;

	tmp = envl->next_link;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (1);
		tmp = tmp->next_link;
	}
	return (0);
}
