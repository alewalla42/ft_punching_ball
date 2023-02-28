/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:27:20 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:16:31 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	*g_core;

char	*rl_gets(char *line_read)
{
	line_read = readline("minishell: ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	minishell(t_tok *tokenl, t_exec *exec, t_env *envl, char *line_read)
{
	ft_parsing(line_read, tokenl);
	ft_expand(tokenl, envl);
	ft_check_expand(tokenl);
	ft_merge_block(tokenl);
	if (ft_check_tokenl(tokenl) == 1)
	{
		free(line_read);
		ft_clean_tokenl(tokenl);
		free(tokenl);
		return (1);
	}
	if (ft_prep_exec(tokenl, exec))
	{
		ft_clean_tokenl(tokenl);
		ft_free_tokenl(tokenl);
		ft_start_exec(exec, envl);
	}
	else
	{
		ft_clean_tokenl(tokenl);
		ft_free_tokenl(tokenl);
	}
	ft_clean_exec_struct(exec);
	free(line_read);
	return (0);
}

void	ft_setup_minishell(t_exec *exec, t_env *envl, char **envp)
{
	g_core = (t_core *)malloc(sizeof(t_core));
	if (g_core == NULL || envl == NULL || exec == NULL)
	{
		free(g_core);
		free(exec);
		free(envl);
		ft_put_error("malloc error");
		exit (1);
	}
	g_core->exec = exec;
	g_core->envl = envl;
	ft_envp_to_envl(envp, envl);
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char	*line_read;
	t_tok	*tokenl;
	t_exec	*exec;
	t_env	*envl;

	(void)ac;
	(void)av;
	exec = (t_exec *)malloc(sizeof(t_exec));
	envl = (t_env *)malloc(sizeof(t_env));
	ft_setup_minishell(exec, envl, envp);
	while (1)
	{
		tokenl = (t_tok *)malloc(sizeof(t_tok));
		if (tokenl == NULL)
			ft_free_before_readline(exec, envl);
		g_core->tokenl = tokenl;
		line_read = NULL;
		line_read = rl_gets(line_read);
		if (line_read == NULL)
			ft_free_on_eof(envl, exec, tokenl, line_read);
		minishell(tokenl, exec, envl, line_read);
	}
	return (0);
}
