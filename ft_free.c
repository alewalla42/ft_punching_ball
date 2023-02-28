/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:56:14 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:05:48 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all_before_exec(void)
{
	ft_clean_tokenl(g_core->tokenl);
	ft_free_tokenl(g_core->tokenl);
	ft_free_envl(g_core->envl);
	free(g_core->exec);
	free(g_core);
	ft_put_error("malloc error");
	exit (1);
}

void	ft_free_all_after_exec(void)
{
	ft_free_envl(g_core->envl);
	ft_clean_exec_struct(g_core->exec);
	free(g_core->exec);
	free(g_core);
	ft_put_error("malloc error");
	exit (1);
}

void	ft_free_in_child(t_exec *exec, t_env *envl)
{
	ft_free_envl(envl);
	ft_clean_exec_struct(exec);
	free(exec);
	free(g_core);
}

void	ft_free_on_eof(t_env *envl, t_exec *exec, \
	t_tok *tokenl, char *line_read)
{
	int	ret;

	ret = atoi(envl->value);
	ft_put_error("exit");
	ft_free_envl(envl);
	free(tokenl);
	free(exec);
	free(g_core);
	free(line_read);
	exit (ret);
}

void	ft_free_before_readline(t_exec *exec, t_env *envl)
{
	ft_free_envl(envl);
	free(exec);
	exit (1);
}
