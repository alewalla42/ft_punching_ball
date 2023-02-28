/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envl_to_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:25:06 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/23 21:19:57 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_listlen(t_env *envl)
{
	int		len;
	t_env	*tmp;

	tmp = envl->next_link;
	len = 1;
	while (tmp->next_link != NULL)
	{
		tmp = tmp->next_link;
		len++;
	}
	return (len);
}

char	*ft_add_to_envp(char *name, char *value)
{
	int		name_len;
	int		value_len;
	int		i;
	int		y;
	char	*line;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	line = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
	if (line == NULL)
		ft_free_all_after_exec();
	if (line == NULL)
		return (NULL);
	i = -1;
	while (name[++i])
		line[i] = name[i];
	line[i] = '=';
	i++;
	y = -1;
	while (value[++y])
		line[i + y] = value[y];
	line[i + y] = '\0';
	return (line);
}

void	ft_free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp[i]);
	free(envp);
	return ;
}

char	**ft_envl_to_envp(t_env *envl)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	i = ft_listlen(envl);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (envp == NULL)
		ft_free_all_after_exec();
	if (envp == NULL)
		return (NULL);
	tmp = envl->next_link;
	i = 0;
	while (tmp->next_link != NULL)
	{
		envp[i] = ft_add_to_envp(tmp->name, tmp->value);
		i++;
		tmp = tmp->next_link;
	}
	envp[i] = ft_add_to_envp(tmp->name, tmp->value);
	envp[++i] = NULL;
	return (envp);
}
