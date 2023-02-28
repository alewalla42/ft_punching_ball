/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:39:31 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:52:48 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(void)
{
	long	i;
	char	*buff;

	i = 0;
	buff = NULL;
	buff = getcwd(buff, ++i);
	while (!buff && i <= 4096)
		buff = getcwd(buff, ++i);
	if (i > 4096)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

int	ft_pwd(void)
{
	char	*buff;

	buff = ft_getcwd();
	if (buff != NULL)
	{
		ft_put_error(buff);
		free(buff);
		return (0);
	}
	else
	{
		ft_put_error("getcwd: cannot access parent directories");
		free(buff);
		return (1);
	}
}
