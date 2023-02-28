/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:26:58 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/25 19:08:22 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_create_new_tab(char *str)
{
	char	**new_tab;

	new_tab = (char **)malloc(sizeof(char *) * 2);
	if (new_tab == NULL)
		return (NULL);
	new_tab[0] = ft_strdup(str);
	new_tab[1] = NULL;
	return (new_tab);
}

char	**ft_add_to_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	if (tab == NULL)
		return (ft_create_new_tab(str));
	else
	{
		while (tab[i])
			i++;
		new_tab = (char **)malloc(sizeof(char *) * (i + 2));
		if (new_tab == NULL)
			return (NULL);
		i = 0;
		while (tab[i])
		{
			new_tab[i] = ft_strdup(tab[i]);
			i++;
		}
		new_tab[i] = ft_strdup(str);
		new_tab[i + 1] = NULL;
		ft_free_tab(tab);
	}
	return (new_tab);
}
