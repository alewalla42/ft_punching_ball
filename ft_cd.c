/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:30:45 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:41:52 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_dir(char *name, t_env *envl)
{
	if (!name)
		return (ft_print_error("HOME not set"));
	if (ft_strcmp(name, "-") == 0)
		name = ft_get_value_from_envl(envl, "OLDPWD");
	if (access(name, F_OK) == 0)
	{
		if (access(name, X_OK) == 0)
		{
			if (ft_is_in_envl(envl, "OLDPWD"))
				ft_change_value(envl, "OLDPWD", ft_getcwd());
			chdir(name);
			if (ft_is_in_envl(envl, "PWD"))
				ft_change_value(envl, "PWD", ft_getcwd());
		}
		else
			ft_return_error_with_name("cd: permission denied: ", name);
		return (0);
	}
	return (ft_return_error_with_name("cd: no such file or directory: ", name));
}

int	ft_cd(int ac, char **av, t_env *envl)
{
	if (ac > 2)
	{
		ft_put_error("cd: too many arguments");
		free(envl->value);
		envl->value = ft_strdup("1");
		return (1);
	}
	if (av[1] == NULL)
		return (ft_change_dir(ft_get_value_from_envl(envl, "HOME"), envl));
	return (ft_change_dir(av[1], envl));
}
