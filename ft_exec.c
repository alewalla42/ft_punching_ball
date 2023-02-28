/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:14:51 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:30:50 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_error_msg(char *str)
{
	if (access(str, X_OK) != 0 && access(str, F_OK) == 0)
	{
		ft_put_error_with_name("Error: permission denied: ", str);
		return (126);
	}
	else
	{
		ft_put_error_with_name("Error: command not found: ", str);
		return (127);
	}
}

int	ft_exec(t_exec *exec, t_env *envl, int fd_in)
{
	int		pip[2];
	int		ret;
	char	**envp;

	envp = NULL;
	if (pipe(pip) == -1)
		return (424242);
	exec->pid = fork();
	if (exec->pid == -1)
		return (424242);
	if (!exec->pid)
	{
		close(pip[0]);
		ft_dup2(exec, pip);
		envp = ft_envl_to_envp(envl);
		ft_close_before_exec(exec, fd_in, pip);
		execve(exec->av[0], exec->av, envp);
		ret = ft_exec_error_msg(exec->av[0]);
		ft_free_tab(envp);
		ft_free_in_child(ft_get_first_exec(exec), envl);
		exit (ret);
	}
	else
		return (ft_parent_return(pip));
}

int	ft_wait_child(int child, int last_pid)
{
	int		i;
	int		status;
	int		pid;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < child)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid && WIFEXITED(status))
			ret = WEXITSTATUS(status);
		if (pid == last_pid && WIFSIGNALED(status))
			ret = WTERMSIG(status) + 128;
	}
	return (ret);
}

void	ft_pipeline(t_exec *exec, t_env *envl, int fd_in)
{
	int		child;
	int		ret;
	t_exec	*tmp;

	tmp = exec;
	child = 0;
	while (tmp)
	{
		if (ft_fork_builtins(tmp, envl, fd_in))
			++child;
		else
		{
			ret = ft_exec(tmp, envl, fd_in);
			if (ret == 4242)
				++child;
			if (ret == 424242)
			{
				ft_putstr_fd("Error: fork failed\n", 2);
				ft_free_all_after_exec();
			}
		}
		tmp = tmp->next_link;
	}
	free (envl->value);
	envl->value = ft_itoa(ft_wait_child(child, ft_get_last_pid(exec)));
}

int	ft_start_exec(t_exec *exec, t_env *envl)
{
	int		fd_in;
	char	*buff;
	t_exec	*tmp;

	tmp = exec;
	if (!tmp->av)
		return (ft_handle_empty_arg(envl));
	fd_in = dup(STDIN_FILENO);
	ft_set_absolut_path(exec, envl);
	signal(SIGINT, SIG_IGN);
	if (tmp->next_link == NULL && ft_isbuiltins(tmp->av[0]))
	{
		buff = ft_itoa(ft_builtins_alone(tmp, envl, fd_in));
		free(envl->value);
		envl->value = buff;
	}
	else
		ft_pipeline(tmp, envl, fd_in);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	signal(SIGINT, inthandler);
	return (0);
}
