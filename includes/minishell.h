/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:29:22 by alewalla          #+#    #+#             */
/*   Updated: 2023/02/28 04:32:27 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include <curses.h>
//# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define OUT 0
# define IN_SINGLE 1
# define IN_DOUBLE 2
# define WORD 0
# define PIPE 1
# define INFILE 2
# define OUTFILE 3
# define APPEND 4
# define HEREDOC 5

typedef struct s_exec	t_exec;
struct s_exec
{
	int		ac;
	char	**av;
	int		infile;
	int		outfile;
	pid_t	pid;
	t_exec	*next_link;
	t_exec	*previous_link;
};

typedef struct s_tok	t_tok;
struct s_tok
{
	char	*data;
	int		type;
	int		status;
	int		merge;
	t_tok	*previous_link;
	t_tok	*next_link;
};

typedef struct s_env	t_env;
struct s_env
{
	char		*name;
	char		*value;
	t_env		*next_link;
};

typedef struct s_arg	t_arg;
struct s_arg
{
	char		*argument;
	int			nbr_arg;
	t_arg		*next;
};

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char		*cmd_user;
	int			*lenght_cmd;
	int			nbr;
	t_arg		*next_arg;
	t_cmd		*next_cmd;
};

typedef struct s_path	t_path;
struct s_path
{
	char	*path_env;
	char	**path_tab;
};

typedef struct s_core	t_core;
struct s_core
{
	t_env	*envl;
	t_tok	*tokenl;
	t_exec	*exec;
};

extern t_core			*g_core;

void	ft_parsing(char *cmd_line, t_tok *tokenl);
void	ft_putstruct(t_tok *token);
void	ft_setup_first_block(t_tok *token);
void	ft_create_word_block(t_tok *token, char data);
void	ft_create_type_block(t_tok *token, int type);
void	ft_create_quote_block(int status, t_tok *token);
void	ft_create_empty_block(t_tok *token);
void	ft_create_empty_block_to_merge(t_tok *tokenl);

void	ft_free_tokenl(t_tok *token);
int		ft_check_tokenl(t_tok *tokenl);
void	ft_check_expand(t_tok *tokenl);
int		ft_prep_exec(t_tok *token, t_exec *exec);
void	ft_free_exec_struct(t_exec *exec);
void	ft_merge_block(t_tok *tokenl);
void	ft_clean_tokenl(t_tok *tokenl);
void	ft_clean_exec_struct(t_exec *exec);
int		ft_get_last_pid(t_exec *exec);
int		ft_isbuiltins(char *str);
int		ft_fork_builtins(t_exec *exec, t_env *envl, int fd_in);
int		ft_builtins(t_exec *tmp, t_env *envl, int fd_in, int fd_out);
t_exec	*ft_get_first_exec(t_exec *exec);
int		ft_print_error(char *str);
void	ft_set_redirection(t_exec *exec, t_tok *tokenl);
int		ft_open_redirection(char *file, int type);
int		ft_exit(t_exec *exec, t_env *envl, int fd_in, int fd_out);
int		ft_builtins_alone(t_exec *exec, t_env *envl, int fd_in);
void	ft_free_all_after_exec(void);
void	ft_free_all_before_exec(void);
void	ft_dup2(t_exec *exec, int *pip);
int		ft_parent_return(int *pip);
void	ft_free_in_child(t_exec *exec, t_env *envl);
void	ft_free_on_eof(t_env *envl, t_exec *exec, \
	t_tok *tokenl, char *line_read);
char	*ft_join_line_read_without_env(char *line_read, int i, char *cpy);
void	ft_free_before_readline(t_exec *exec, t_env *envl);
int		ft_skip_dollar(char *line, int i);
int		ft_print_error(char *str);
int		ft_handle_empty_arg(t_env *envl);
void	ft_put_error_with_name(char *str, char *name);
int		ft_return_error_with_name(char *str, char *name);
void	ft_put_error(char *str);
int		ft_return_error(char *str);
void	ft_close_before_exec(t_exec *exec, int fd_in, int pip[2]);

//////

void	ft_expand(t_tok *tokenl, t_env *envl);

char	*alloc_line_char_read(char *line_read, int *i, char c);
char	**alloc_line_read(char **tab_line, char *line_read);
int		count_line_char_read1(char *line_read, int *i, int count, char c);
int		count_line_read(char *line_read);
char	**alloc_cmd(char *line_read);
void	ft_put_exec_struct(t_exec	*exec);

char	**ft_alloc_path_tab(t_env *envl);

char	*ft_test_cmd(t_core *core, char *arg);
int		ft_heredoc(char *str);

int		ft_start_exec(t_exec *exec, t_env *envl);
void	ft_set_absolut_path(t_exec *exec, t_env *envl);

//t_list	*init_cmd(void);
//t_cmd	*add_nbr_cmd(t_list *tab_list, int new_nbr);
//void	delete_nbr_cmd(t_list *tab_list);
//void	print_cmd(t_list *tab_list);

t_arg	*init_arg(void);
t_arg	*add_nbr_arg(t_cmd *tab_list, int new_nbr);
void	delete_nbr_arg(t_cmd *tab_list);
void	print_arg(t_cmd *tab_list);

int		ft_get_len(int n);
char	*ft_create_str(int len, int n, int neg, char *str);
char	*ft_itoa(int n);
char	*alloc_line_char_read2(char *line_read, int *i);

char	*ft_create_str(int len, int n, int neg, char *str);
int		ft_get_len(int n);

int		ft_cd(int ac, char **av, t_env *envl);
int		ft_change_dir(char *name, t_env *envl);
int		ft_echo(int ac, char **arg);
int		ft_check_flags(char **arg);
void	ft_env(char **envp);
int		ft_pipe(char **f_input, char **f_ouput, char **envp);
int		ft_pwd(void);
char	*ft_getcwd(void);
int		ft_tab_len(char **tab);
void	ft_new_tab(char **dest, char *add);
int		ft_export(int ac, char **arg, t_env *envp);
void	ft_unset(char **arg, t_env *envl);
void	inthandler(int sig);

char	*ft_get_name(char *str, char stop);
char	*ft_get_value(char *str);
void	ft_join_value(t_env *envl, char *name, char *value);

void	ft_print_envl(t_env	*envl);
void	ft_envp_to_envl(char **envp, t_env *envl);
void	ft_add_to_envl(t_env *envl, char *name, char *value);
void	ft_remove_from_envl(t_env *envl, char *name);
void	ft_change_value(t_env *envl, char *name, char *value);
int		ft_is_in_envl(t_env *envl, char *name);
void	ft_free_envl(t_env *envl);
char	*ft_get_value_from_envl(t_env *envl, char *name);

char	*ft_replace_dollar(char *line, t_env *envl);

char	**ft_envl_to_envp(t_env *envl);
void	ft_free_envp(char **envp);

//void	ft_exit(int nbr, t_env *envl, char **arg);

#endif