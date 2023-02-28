/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:47:21 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 17:29:51 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_block_data(char *data1, char *data2)
{
	int		i;
	char	*ret;

	if (data2 == NULL)
		return (data1);
	if (data1 == NULL)
		return (data2);
	ret = (char *)malloc(sizeof(char) \
		* (ft_strlen(data1) + ft_strlen(data2) + 1));
	if (ret == NULL)
		ft_free_all_before_exec();
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (*data1)
		ret[++i] = *data1++;
	while (*data2)
		ret[++i] = *data2++;
	ret[++i] = '\0';
	return (ret);
}

void	ft_free_next_block(t_tok *tokenl, char *buff)
{
	t_tok	*tmp;

	tokenl->merge = tokenl->next_link->merge;
	free(tokenl->next_link->data);
	free(tokenl->data);
	tokenl->data = buff;
	tmp = tokenl->next_link->next_link;
	free(tokenl->next_link);
	tokenl->next_link = tmp;
}

void	ft_merge_block(t_tok *tokenl)
{
	char	*buff;

	if (tokenl->merge == 1 && tokenl->next_link != NULL)
	{
		if (tokenl->next_link->type == WORD && tokenl->next_link->data != NULL)
		{
			if (tokenl->data == NULL)
				buff = ft_strdup(tokenl->next_link->data);
			else
			{
				if (tokenl->next_link->data)
					buff = ft_strjoin(tokenl->data, tokenl->next_link->data);
				else
					buff = ft_strdup(tokenl->data);
			}
			ft_free_next_block(tokenl, buff);
			ft_merge_block(tokenl);
		}
	}
	if (tokenl->next_link != NULL)
		ft_merge_block(tokenl->next_link);
}
