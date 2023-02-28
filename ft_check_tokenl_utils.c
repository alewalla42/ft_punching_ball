/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokenl_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:42:57 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:28:02 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
