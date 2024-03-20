/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/19 09:30:32 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "../lib/libft/srcs/libft.h"

typedef struct s_parser_state
{
	int		i;
	int		k;
	char	*new_cmd;
	int		dollar;
}	t_parser_state;

typedef struct cd_state
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
}	t_cd_state;
typedef struct s_env_var
{
	int					is_set;
	char				*v_name;
	char				*v_value;
	bool				exported;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_split_state
{
	int				i;
	int				j;
	int				k;
	int				inside_quotes;
	int				inside_dquotes;
	struct s_shell	*shell;
}	t_split_state;

typedef struct s_shell
{
	int			status;
	int			term_sig;
	int			exit_status;
	int			i;
	int			len;
	bool		quote;
	bool		dquote;
	char		*error_msg;
	char		**envp;
	t_list		*cmd_list;
	t_env_var	*env_list;
}	t_shell;

extern int	g_sigstat;

int			kv_execute_command(t_shell *shell);
int			kv_check_sigterm(t_shell *shell);
int			kv_count(char const *s, char c);
int			kv_count_cmds(char **cmd);
int			kv_arr_len(char **arr);
int			kv_parent_builtin(t_shell *shell);
int			kv_count_expand(char *cmd);
int			kv_child_builtin(t_shell *shell);
int			kv_is_valid_env_name(const char *name);
int			kv_exit_command(t_shell *shell);
int			kv_cd_command(t_shell *shell);
int			kv_env_command(t_shell *shell);
int			kv_pwd_command(void);
int			kv_setenv(t_shell *shell, const char *name, const char *value);
int			kv_unsetenv(t_shell *shell, const char *name);
int			kv_process_env_var(t_shell *shell, char *env_var);
int			kv_free_cd_paths(char *path, char *oldpwd, char *err_msg);
int			kv_open_quotes(t_shell *shell);
int			kv_print_export(t_shell *shell);
int			kv_find_delimiter(const char *str);
int			kv_process_n(char **cmd, int *n_flag);
int			find_or_create_env_var(t_shell *shell, const char *name, \
	const char *value, bool exported);
int			kv_check_nested_shell(t_shell *shell);
bool		kv_valid_cmd(char *cmd);
char		*kv_getinput(t_shell *shell);
char		*kv_strip_cmd(char *cmd);
char		*kv_path_creator(t_shell *shell, char **cmd);
char		*kv_strip_cmd(char *cmd);
char		*kv_cmd_parser(char *cmd, t_shell *shell);
char		*kv_remove_outer_quotes(char *str);
char		**kv_split_ignore_quotes(char const *s, char c, t_shell *shell);
char		*kv_build_and_check_path(const char *base, const char *cmd);
int			kv_parsing_stuff(char *cmd, t_shell *shell,
				t_parser_state *state, int *i);
void		kv_add_env_var(t_shell *shell, const char *env_str);
void		kv_redirecting(t_list *pipex);
void		kv_set_signals(void);
void		kv_sigint_handler(int signo);
void		kv_child_handler(int signo);
void		kv_free_exit(t_shell *shell, int exit_code);
void		kv_parent(t_shell *shell);
void		kv_freepipex(t_list *pipex);
void		kv_replace_tabs(char *str);
void		kv_free_paths(char **paths);
void		kv_free_perror(char *name, char *value, int error_msg);
void		kv_redir_open(char **argv, t_list *cmd_list);
void		kv_pre_exec_checks(t_shell *shell, char *cmd);
void		kv_command_not_found(t_shell *shell);
void		kv_print_error(char *error_msg, char *error_cmd, int shell_path);
void		kv_handle_redirection_parser(char *cmd, int *i, \
	t_parser_state *state);
void		kv_wait_parents(t_shell *shell);
void		kv_handle_redirection(t_list *cmd_list);
void		kv_handle_quotes(char c, t_shell *shell);
void		kv_free_perror(char *name, char *value, int error_msg);
void		readline_heredoc(char *heredoc, int fd);
void		kv_write_redir(char *redir, char *filename, t_list *cmd_list);
void		kv_copy_env(t_env_var	*current, char **envp_copy, int len);
void		kv_check_for_heredoc(t_list *cmd_list);
int			kv_open_file_read(char *file);
int			kv_open_file_write(char *file);
void		kv_check_minishell(t_shell *shell);
void		kv_init_local_vars(int *i, int *k, t_shell *shell);
size_t		kv_longest_env(t_shell *shell);
int			kv_count_env_var(t_env_var *env_var);
char		*kv_get_env_char(t_shell *shell, char *name);
int			kv_get_exit_status(char *new_cmd, int *i, t_shell *shell);
int			kv_env_list_v(char *new_cmd, const char *cmd, \
	int *i, t_shell *shell);
t_list		*kv_new_lst(t_shell *shell, char **argv);
t_env_var	*kv_getenv(t_shell *shell, const char *name);

#endif