/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:10:38 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/21 17:56:24 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_and_return(int *pip)
{
	close(pip[1]);
	return (pip[0]);
}

int	ft_heredoc(char *str)
{
	char	*line_read;
	int		pip[2];
	int		i;

	i = 0;
	if (pipe(pip) == -1)
		return (-2);
	while (1)
	{
		line_read = readline("heredoc> ");
		if (line_read == NULL)
		{
			write(1, "exit\n", 5);
			return (ft_close_and_return(pip));
		}
		if (ft_strcmp(line_read, str) == 0)
		{
			free(line_read);
			return (ft_close_and_return(pip));
		}
		ft_putstr_fd(line_read, pip[1]);
		ft_putchar_fd('\n', pip[1]);
		free(line_read);
	}
}
