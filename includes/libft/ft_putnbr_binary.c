/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:01:29 by alewalla          #+#    #+#             */
/*   Updated: 2023/01/19 16:43:17 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_binary2(int nbr)
{
	char		*base;

	base = "01";
	if (nbr >= 2)
		ft_putnbr_binary2(nbr >> 1);
	write(1, &base[nbr % 2], 1);
}

void	ft_putnbr_binary(int nbr)
{
	if (nbr == -2147483648)
	{
		write(1, "-10000000000000000000000000000000", 33);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	ft_putnbr_binary2(nbr);
	write(1, "\n", 1);
}
