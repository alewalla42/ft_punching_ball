/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:55:59 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/27 18:29:38 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		ft_free_all_after_exec();
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++j])
		str[++i] = s1[j];
	j = -1;
	while (s2[++j])
		str[++i] = s2[j];
	str[++i] = '\0';
	free(s1);
	return (str);
}

char	**ft_alloc_path_tab(t_env *envl)
{
	int		i;
	char	*path;
	char	*tmp_path;
	char	**path_tab;
	t_env	*tmp;

	i = -1;
	tmp = envl;
	path = ft_get_value_from_envl(tmp, "PATH");
	if (path == NULL)
		return (NULL);
	tmp_path = malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (tmp_path == NULL)
		ft_free_all_after_exec();
	tmp_path = ft_strcpy(tmp_path, path);
	path_tab = ft_split(tmp_path, ':');
	while (path_tab[++i] != NULL)
		path_tab[i] = ft_strjoin_and_free(path_tab[i], "/");
	free(tmp_path);
	return (path_tab);
}

int	ft_has_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == '/')
			return (1);
	return (0);
}

void	ft_test_absolut_path(t_exec *exec, char **path_tab)
{
	int		i;
	char	*tmp;

	i = -1;
	if (exec->av == NULL)
		return ;
	while (path_tab[++i] != NULL)
	{
		if (!ft_isbuiltins(exec->av[0]) && !ft_has_slash(exec->av[0]))
		{
			tmp = ft_strjoin(path_tab[i], exec->av[0]);
			if (access(tmp, F_OK) == 0)
			{
				free(exec->av[0]);
				exec->av[0] = tmp;
				break ;
			}
			free(tmp);
		}
	}
	if (exec->next_link != NULL)
		ft_test_absolut_path(exec->next_link, path_tab);
}

void	ft_set_absolut_path(t_exec *exec, t_env *envl)
{
	char	**path_tab;

	path_tab = ft_alloc_path_tab(envl);
	if (path_tab == NULL)
		return ;
	ft_test_absolut_path(exec, path_tab);
	ft_free_tab(path_tab);
}
