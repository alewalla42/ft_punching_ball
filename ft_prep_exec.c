/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:14:58 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:26:33 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_exec_struct(t_exec *exec)
{
	t_exec	*tmp;

	tmp = NULL;
	if (exec->av != NULL)
		ft_free_tab(exec->av);
	if (exec->infile != -1)
		close(exec->infile);
	if (exec->outfile != -1)
		close(exec->outfile);
	if (exec->next_link != NULL)
		tmp = exec->next_link;
	exec->next_link = NULL;
	if (tmp != NULL)
		ft_clean_exec_struct(tmp);
	free(tmp);
}

int	ft_open_redirection(char *file, int type)
{
	int		fd;

	if (type == INFILE)
	{
		if (access(file, F_OK) == 0)
			fd = open(file, O_RDONLY);
		else
		{
			ft_put_error_with_name(\
			"Error: No such file or directory: %s\n", file);
			return (-2);
		}
	}
	else if (type == OUTFILE)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

void	ft_create_new_exec_block(t_exec *exec)
{
	t_exec	*new_exec;

	new_exec = (t_exec *)malloc(sizeof(t_exec));
	if (new_exec == NULL)
		ft_free_all_after_exec();
	new_exec->ac = 0;
	new_exec->av = NULL;
	new_exec->infile = -1;
	new_exec->outfile = -1;
	new_exec->next_link = NULL;
	new_exec->previous_link = exec;
	exec->next_link = new_exec;
}

void	ft_setup_first_exec_block(t_exec *exec)
{
	exec->ac = 0;
	exec->av = NULL;
	exec->infile = -1;
	exec->outfile = -1;
	exec->next_link = NULL;
	exec->previous_link = NULL;
}

int	ft_prep_exec(t_tok *token, t_exec *exec)
{
	t_tok	*tmp;

	tmp = token;
	ft_setup_first_exec_block(exec);
	while (tmp)
	{
		if (tmp->type == WORD && tmp->data != NULL)
		{
			exec->av = ft_add_to_tab(exec->av, tmp->data);
			exec->ac++;
		}
		ft_set_redirection(exec, tmp);
		if (tmp->type == PIPE)
			ft_create_new_exec_block(exec);
		while (exec->next_link != NULL)
			exec = exec->next_link;
		tmp = tmp->next_link;
	}
	return (1);
}
