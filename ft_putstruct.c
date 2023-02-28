/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:11:06 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 03:46:50 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_exec_struct(t_exec	*exec)
{
	t_exec	*tmp;

	tmp = exec;
	while (tmp->next_link != NULL)
	{
		printf("ac = %d\n", tmp->ac);
		if (tmp->av != NULL)
			ft_puttab(tmp->av);
		printf("infile = %d\n", tmp->infile);
		printf("outfile = %d\n", tmp->outfile);
		tmp = tmp->next_link;
	}
	printf("ac = %d\n", tmp->ac);
	if (tmp->av != NULL)
		ft_puttab(tmp->av);
	printf("infile = %d\n", tmp->infile);
	printf("outfile = %d\n", tmp->outfile);
	printf("\n------------------\n");
}

void	ft_putstruct(t_tok *token)
{
	t_tok	*tmp;

	tmp = token;
	while (tmp->next_link != NULL)
	{
		printf("data = %s\n", tmp->data);
		printf("type = %d\n", tmp->type);
		printf("status = %d\n", tmp->status);
		printf("merge = %d\n\n", tmp->merge);
		tmp = tmp->next_link;
	}
	printf("data = %s\n", tmp->data);
	printf("type = %d\n", tmp->type);
	printf("status = %d\n", tmp->status);
	printf("merge = %d\n", tmp->merge);
	printf("\n------------------\n");
}
