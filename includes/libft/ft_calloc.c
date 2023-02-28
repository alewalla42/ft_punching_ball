/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:38:27 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/23 21:17:39 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	if (size == 0 || count == 0)
	{
		count = 1;
		size = 1;
	}
	dest = malloc(count * size);
	if (!dest)
		return (NULL);
	if (!dest)
		return (0);
	ft_bzero(dest, count * size);
	return (dest);
}
