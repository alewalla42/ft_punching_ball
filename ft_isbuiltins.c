/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:15:58 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/20 20:56:33 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltins(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	return (0);
}
