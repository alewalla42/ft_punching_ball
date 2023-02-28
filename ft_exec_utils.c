/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:21:25 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:31:20 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_last_pid(t_exec *exec)
{
	t_exec	*tmp;

	tmp = exec;
	while (tmp->next_link)
		tmp = tmp->next_link;
	return (tmp->pid);
}

t_exec	*ft_get_first_exec(t_exec *exec)
{
	t_exec	*tmp;

	tmp = exec;
	while (tmp->previous_link)
		tmp = tmp->previous_link;
	return (tmp);
}

void	ft_set_redirection(t_exec *exec, t_tok *tmp)
{
	if (tmp->type == INFILE)
	{
		if (exec->infile != -1)
			close(exec->infile);
		exec->infile = ft_open_redirection(tmp->data, INFILE);
		if (exec->infile == -2)
			return ;
	}
	if (tmp->type == OUTFILE || tmp->type == APPEND)
	{
		if (exec->outfile != -1)
			close(exec->outfile);
		exec->outfile = ft_open_redirection(tmp->data, tmp->type);
	}
	if (tmp->type == HEREDOC)
	{
		if (exec->infile != -1)
			close(exec->infile);
		exec->infile = ft_heredoc(tmp->data);
	}
}

int	ft_handle_empty_arg(t_env *envl)
{
	free(envl->value);
	envl->value = ft_strdup("0");
	return (0);
}

void	ft_close_before_exec(t_exec *exec, int fd_in, int pip[2])
{
	close(fd_in);
	close(pip[1]);
	if (exec->infile != -1)
		close(exec->infile);
	if (exec->outfile != -1)
		close(exec->outfile);
}
