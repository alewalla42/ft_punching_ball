/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:35:39 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:15:36 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtins_alone(t_exec *exec, t_env *envl, int fd_in)
{
	int	fd_out;
	int	ret;

	fd_out = dup(STDOUT_FILENO);
	if (exec->infile != -1)
		dup2(exec->infile, STDIN_FILENO);
	if (exec->outfile != -1)
		dup2(exec->outfile, STDOUT_FILENO);
	ret = ft_builtins(exec, envl, fd_in, fd_out);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (ret);
}

int	ft_builtins(t_exec *tmp, t_env *envl, int fd_in, int fd_out)
{
	int	ret;

	ret = 0;
	if (tmp->av == NULL)
		return (1);
	if (ft_strcmp(tmp->av[0], "cd") == 0)
		ret = ft_cd(tmp->ac, &tmp->av[0], envl);
	else if (ft_strcmp(tmp->av[0], "echo") == 0)
		ret = ft_echo(tmp->ac, &tmp->av[1]);
	else if (ft_strcmp(tmp->av[0], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(tmp->av[0], "env") == 0)
		ft_print_envl(envl);
	else if (ft_strcmp(tmp->av[0], "export") == 0)
		ret = ft_export(tmp->ac, &tmp->av[1], envl);
	else if (ft_strcmp(tmp->av[0], "unset") == 0)
		ft_unset(&tmp->av[1], envl);
	else if (ft_strcmp(tmp->av[0], "exit") == 0)
		ret = ft_exit(tmp, envl, fd_in, fd_out);
	else
		return (0);
	return (ret);
}

void	ft_dup2(t_exec *exec, int *pip)
{
	if (exec->next_link != NULL)
		dup2(pip[1], STDOUT_FILENO);
	if (exec->infile != -1)
		dup2(exec->infile, STDIN_FILENO);
	if (exec->outfile != -1)
		dup2(exec->outfile, STDOUT_FILENO);
}

int	ft_parent_return(int *pip)
{
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	return (4242);
}

int	ft_fork_builtins(t_exec *exec, t_env *envl, int fd_in)
{
	int	pip[2];
	int	ret;

	if (!ft_isbuiltins(exec->av[0]))
		return (0);
	if (pipe(pip) == -1)
		return (424242);
	exec->pid = fork();
	if (exec->pid == -1)
		return (424242);
	if (!exec->pid)
	{
		close(pip[0]);
		ft_dup2(exec, pip);
		close(pip[1]);
		close(exec->outfile);
		close(exec->infile);
		ret = ft_builtins(exec, envl, fd_in, -1);
		close(fd_in);
		ft_free_in_child(ft_get_first_exec(exec), envl);
		exit (ret);
	}
	else
		return (ft_parent_return(pip));
}
