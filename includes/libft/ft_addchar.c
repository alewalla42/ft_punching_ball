/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:18:25 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/23 21:17:20 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_addchar(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new == NULL)
		return (NULL);
	if (str != NULL)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}
