/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:42:29 by alewalla          #+#    #+#             */
/*   Updated: 2023/01/19 17:08:37 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hexa2(int nbr)
{
	char		*base;

	base = "0123456789ABCDEF";
	if (nbr >= 16)
		ft_putnbr_hexa2(nbr >> 4);
	write(1, &base[nbr % 16], 1);
}

void	ft_putnbr_hexa(int nbr)
{
	if (nbr == -2147483648)
	{
		write(1, "-80000000", 9);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	ft_putnbr_hexa2(nbr);
	write(1, "\n", 1);
}
