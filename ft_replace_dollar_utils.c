/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:00:42 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 16:27:55 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_line_read_without_env(char *line_read, int i, char *cpy)
{
	int	y;
	int	nbr_n;

	y = i;
	while (line_read[y] && line_read[y] != ' ' && line_read[y] != '<'
		&& line_read[y] != '>' && line_read[y] != '|'
		&& line_read[y] != 34 && line_read[y] != 39)
		y++;
	nbr_n = y - i;
	while (line_read[y])
		y++;
	cpy = malloc(sizeof(char) * (y - nbr_n + 1));
	if (cpy == NULL)
		ft_free_all_before_exec();
	return (cpy);
}

int	ft_skip_dollar(char *line, int i)
{
	while (line[++i] == '$')
		;
	return (--i);
}
