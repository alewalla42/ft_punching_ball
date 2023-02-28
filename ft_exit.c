/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:14:59 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 23:50:01 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	too_many_args(void)
{
	ft_putstr_fd("minishell: too many arguments\n", 2);
	return (1);
}

int	numeric_error(char *s)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	check_if_numeric(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		i++;
		j++;
	}
	if (!s[i])
		return (0);
	while (s[i] == '0' && s[i])
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
		j++;
	}
	if (j < 20)
		return (1);
	else
		return (0);
}

int	ft_exit(t_exec *exec, t_env *envl, int fd_in, int fd_out)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (!exec->av[1])
		ret = ft_atoi(envl->value);
	else if (!check_if_numeric(exec->av[1]))
		ret = numeric_error(exec->av[1]);
	else
	{
		ret = ft_atoi(exec->av[1]);
		if (exec->ac > 2)
			return (too_many_args());
	}
	ft_free_envl(envl);
	exec = ft_get_first_exec(exec);
	ft_clean_exec_struct(exec);
	free(exec);
	close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	free(g_core);
	exit (ret);
	return (ret);
}
