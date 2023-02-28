/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:21:43 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/21 17:58:22 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **arg, t_env *envl)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (ft_strcmp(arg[i], "_") != 0)
			ft_remove_from_envl(envl, arg[i]);
	return ;
}
