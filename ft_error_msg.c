/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:34:49 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:42:24 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_error_with_name(char *str, char *name)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_put_error_with_name(char *str, char *name)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_put_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_return_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
