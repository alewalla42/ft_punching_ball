/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:22:18 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/23 18:29:02 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_block_inbetween(t_tok *tmp, char **split)
{
	t_tok	*new;
	int		i;

	i = 0;
	while (split[++i] != NULL)
	{
		if (split != NULL)
		{
			new = NULL;
			new->data = ft_strdup(split[i]);
			new->type = 0;
			new->status = OUT;
			new->merge = 0;
			new->previous_link = tmp;
			new->next_link = tmp->next_link;
			tmp->next_link = new;
			tmp->merge = 0;
		}
	}
}

char	*ft_strdup_and_free(char *str, char *to_free)
{
	char	*new;

	new = ft_strdup(str);
	free(to_free);
	return (new);
}

void	ft_check_expand(t_tok *tokenl)
{
	t_tok	*tmp;
	char	**split;

	tmp = tokenl;
	while (tmp)
	{
		if (tmp->status == OUT && tmp->type == 0)
		{
			if (tmp->data != NULL)
			{
				split = ft_split(tmp->data, ' ');
				if (split[0])
				{
					tmp->data = ft_strdup_and_free(split[0], tmp->data);
					ft_create_block_inbetween(tmp, split);
				}
				ft_free_tab(split);
			}
		}
		tmp = tmp->next_link;
	}
}
