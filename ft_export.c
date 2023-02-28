/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:49:16 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 19:49:39 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_equal(t_env *envl, char *arg)
{
	char	*name;
	char	*value;

	name = ft_get_name(arg, '=');
	value = ft_get_value(arg);
	if (ft_strcmp(name, "_") == 0)
	{
		free(name);
		free(value);
		return ;
	}
	if (ft_is_in_envl(envl, name))
	{
		ft_change_value(envl, name, value);
		free(name);
	}
	else
		ft_add_to_envl(envl, name, value);
}

int	ft_print_and_return(char *arg)
{
	if (arg == NULL)
		return (ft_return_error("man export"));
	else
	{
		ft_put_error_with_name("`%s': not a valid  identifier", arg);
		return (1);
	}
}

int	ft_export(int ac, char **av, t_env *envl)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (ac == 1)
		return (ft_print_and_return(NULL));
	while (av[++i] != NULL)
	{
		if (!ft_isalpha(av[i][0]) && av[i][0] != '_')
			ret = ft_print_and_return(av[i]);
		else if (ft_findstr(av[i], "=") != -1)
		{
			if ((ft_findstr(av[i], "-=") + 1) != ft_findstr(av[i], "="))
				ft_export_equal(envl, av[i]);
			else
				ret = ft_print_and_return(av[i]);
		}
	}
	return (ret);
}
