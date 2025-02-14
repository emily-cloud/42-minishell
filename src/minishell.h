/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlane <rlane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:10:12 by hai               #+#    #+#             */
/*   Updated: 2024/11/12 14:08:45 by rlane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
// For waitpid and associated macros
# include <sys/wait.h>
// For pid_t
# include <sys/types.h>
// file control options inc open, close, redirect etc
# include <fcntl.h>
// for path_max
# include <limits.h>
// for bool
# include <stdbool.h>
// for signalling
# include <signal.h>
// for termios, to disable the ^C report
# include <termios.h>
// for path search
# include <sys/stat.h>
// for errno
# include <errno.h>

//Global Var
// Flag to track SIGINT signal
extern volatile sig_atomic_t	g_sigint_received;

// # define ORANGE "\033[38;5;208m"
// # define GREEN "\033[32m"
// # define RESET "\033[0m"

# define ORANGE
# define GREEN
# define RESET

# define MAX_PATH 4096

# define SPACE_CHAR 1
# define EQUALS_CHAR 2
# define DOLLAR_CHAR 3
# define QUOTE_CHAR 4

# define NOT_EXPORTED 0
# define EXPORTED 1
# define EXPORTED_ONLY 2
# define RESET_QUOTES 1

# define RESET_STATIC 1

# define HEREDOC_ERROR "Minishell: warning: here-document delimited by\
 end-of-file (wanted `"
# define SYNTAX_ERROR "Minishell: syntax error near unexpected token `"

typedef enum e_node_type
{
	OP_PIPE,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_REDIR_APPEND,
	OP_HEREDOC,
	OP_AND,
	OP_OR,
	DELIMITER,
	CMD,
	ARG_FILE,
	ASSIGN_VAR,
	SUB_SHELL,
	FILE_OR_PATH,
}	t_node_type;

typedef struct s_env_node
{
	char				*name;
	char				*value;
	int					exported;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_shell
{
	t_env_node			*env;
	int					last_exit_status;
	int					original_stdin;
	int					original_stdout;
	int					original_stderr;

}	t_shell;

typedef struct s_token_vars
{
	int					open_quote;
	int					open_bracket;
	size_t				string;
	size_t				i;
	int					op_len;
}	t_token_vars;

typedef struct s_wildcards_vars
{
	char		*temp1;
	char		*temp2;
	char		*copy;
	int			i;
	int			array_len;
}	t_wildcards_vars;

typedef struct s_arg_node
{
	char				*content;
	int					quote_flag;
	struct s_arg_node	*next;
}	t_arg_node;

// for filter_ls_list
typedef struct s_filter_data
{
	t_arg_node			*ls_list;
	t_arg_node			*filtered_list;
	char				**segments;
	int					array_len;
}	t_filter_data;

//for wildcard vars
typedef struct s_wc_vars
{
	t_arg_node			*temp;
	t_arg_node			*next_temp;
	t_arg_node			*filtered_list;
	t_arg_node			*prev;
	t_arg_node			*ls_list;
}	t_wc_vars;

// main node for commands and OPs
// for arg quote_flag array: 0 -no quote, 1 -single quote and 2 -double quote
typedef struct s_node
{
	t_shell				*shell;
	t_node_type			type;
	int					*quote_flag;
	char				*content;
	char				**args;
	t_arg_node			*args_list;
	int					presedence;
	int					active_fd_out;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

//main
t_node			*fill_nodes(char **tokens, t_shell *shell);
void			content_to_args(t_node *node);
int				process_arg_content(t_node *node, int *i, int *len);
char			*trim_quotes(char *str);
void			exec_tree(t_node *top);
void			parse_line(char *line, t_shell *shell);
void			exec_cmd(t_node *node);
void			recurse_expand_dollar(t_node *node);
t_shell			*init_shell(char **envp, int export_status);
t_node			*init_node(t_shell *shell);
t_node			*init_pre_node(char *token, t_shell *shell,
					int prev_is_redirection);
void			init_signal_handlers(void);
void			call_external_cmd(t_node *node, char *path);
void			set_last_exit_status(t_node *node, int status);
void			set_last_exit_status_exit_success(t_node *node, int status);
char			*string_replace(char *string, char *target, char *replace);
int				check_var_name(char *s);
void			exit_child(t_node *node);
t_node			*build_tree(t_node *top);
void			build_tree2(t_node **top, t_node **root, t_node **prev,
					t_node **prev_root);
void			exec_tree(t_node *node);

//tokenize
void			tokenize(const char *s, char ***tokens);
int				handle_brackets(char c, int open_bracket);
int				is_op(const char *s);
size_t			count_tokens(const char *s);
void			organize_tokens(char ***tokens);
void			check_space(char *temp, char *space_loc);

//free
void			free_nodes(t_node *top);
void			free_shell(t_shell *shell);
void			free_env_list(t_env_node *head);
void			free_env_node(t_env_node *node);

//env_list functions
t_env_node		*get_env_node(t_env_node *head, char *name);
void			set_env_list(t_shell *head, char **envp, int export_status);
void			add_env_node(char **str, t_env_node *head, int export_status);
t_env_node		*create_node(char **str, int export_status);
int				handle_quotes(char c, int open_quote, int reset);
char			**convert_env_to_array(t_env_node *env);
void			reset_or_add_env_var(t_node *node, char *name, char *value,
					int exported);
void			sort_list(t_env_node **head);
int				count_env_nodes(t_env_node *env);

//exec_nodes functions
void			exec_assign_var(t_node *node);
void			exec_sub_shell(t_node *node);
void			exec_and(t_node *node);
void			exec_or(t_node *node);
void			exec_path_search(t_node *node);
void			set_node_type(char **tokens, int i, t_node *node);
void			set_presedence(t_node *node);

//expand dollar
void			expand_dollar_args(t_node *node);
char			*expand_dollar_string(t_node *node, char *str);
void			update_qt_state(char c, int *in_single_qt, int *in_double_qt);
char			*string_replace(char *string, char *target, char *replace);
int				replace_variable(t_node *node, int arg, int i, int j);
char			*expand_dollar_line(char *input, t_node *node);
char			*build_result_string(char *input, t_node *node);

//builtin functions
void			cmd_cd(t_node *node);
void			set_env_value(t_env_node *env, char *name, char *value,
					int export_status);
void			cmd_echo(t_node *node);
void			cmd_env(t_node *head);
void			cmd_unset(t_node *node);
void			cmd_export(t_node *node);
void			expand_tilda(t_node *node);
void			print_variable(t_env_node *env, char *name);
void			assign_path(char **path, t_env_node *env, char *name);
void			ch_path(char *path, t_node *node);
void			ch_home_sub(char *path, t_node *node);
void			ch_home(t_node *node);
void			ch_oldpwd(t_node *node);

//redirect functions
void			exec_redir_in(t_node *current, int reset);
void			exec_redir_out_append(t_node *current, int reset);
void			parent_process(t_node *current, pid_t pid);
void			open_check(t_node *current, int *fd);
void			check_fd_an_dup2(int fd, int fd2, t_node *node);
int				fork_and_check_pid(void);
void			exec_pipe(t_node *node);

//heredoc functions
void			exec_heredoc(t_node *node);
void			recurse_heredocs(t_node *node, int pipe_fd[2]);
size_t			get_var_length(char *input, size_t *i);
size_t			handle_var_expansion(char *input, size_t var_len,
					size_t i, t_node *node);
char			*my_strndup(char *s, size_t n);
char			*get_var_value(char *var_name, t_node *node);

//utils
void			reset_stin_stout(t_node *node);
int				strlen_cmp(char *str1, char *str2);
int				my_strcmp(const char *str1, const char *str2);
int				is_all_spaces(char *line);

//wildcards
void			expand_wildcards(t_node *node);
t_arg_node		*filter_ls_list(t_arg_node *ls_list, char **segments);
int				count_star(char const *s);
int				star_process_substring(char **array, const char *s, size_t *i,
					size_t *string);
void			get_ls_list(t_arg_node **ls_list, t_shell *shell);
void			init_filter_data(t_filter_data *data, t_arg_node *ls_list,
					char **segments);
int				handle_empty_segments(t_filter_data *data);
void			process_node(t_filter_data *data, t_arg_node *current);
int				process_segment(t_filter_data *data, char **copy, int i);
int				handle_last_occurrence(t_filter_data *data, char **copy, int i);
void			handle_last_segment(t_filter_data *data, t_arg_node *current,
					char *copy);

//arg_list_utils
t_arg_node		*arg_list_new(char *content, int quote_flag);
t_arg_node		*arg_list_last(t_arg_node *lst);
void			arg_list_free(t_arg_node *head);
void			arg_list_add_back(t_arg_node **head, t_arg_node *new);
int				arg_list_size(t_arg_node *lst);
void			args_list_to_array(t_node *node);

//input_error_checks
int				input_error_check(t_node *top);
void			write_error_message(t_node *top, char *message);
int				is_type_op(t_node_type type);
int				check_top(t_node *top);
int				check_pipe_and_or(t_node *top);
int				check_cmd(t_node *top);

//parse
int				ft_count_array(char **s);
void			cmd_pwd(t_node *node);
void			cmd_help(void);

//print debug
void			print_tree(t_node *root);
void			print_args_list(t_arg_node *top);
void			print_simple_list(t_node *top);
void			print_array(char **array, char *name);

#endif //MINISHELL_H
