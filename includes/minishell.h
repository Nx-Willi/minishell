/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/08 19:41:16 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SH_NAME	"miniche"
# define FALSE		0
# define TRUE		1
# define CTRL_C		2
//# define CMD "ls -la | grep $TESTENV h f"
//# define CMD "/sbin/ifconfig | grep 'inet ' | awk '{if(NR==1) print 2}'"
//# define CMD "\"cat $TESTENV\""
//# define CMD "lsblk | grep loop0 | grep \"lvm\" | wc -l | ls -l -a -v -o -p"
//# define CMD "echo \"TESTENVtoto\""
//# define CMD "ls -la -l | -o | wc"

enum	e_type_token
{
	WORD = 1,
	QUOTE,
	D_QUOTE,
	NLINE,
	WHITE_SPACE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	PIPE,
	DOLLAR,
	BACKSLASH
};


//-Structures-------------------------------------------------------------------
typedef struct s_infos		t_infos;
typedef struct s_env		t_env;
typedef struct s_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;

struct s_env
{
	int		from_env;
	char	*variable;
	t_env	*next;
};

struct	s_infos
{
	char	*prompt;
//	char	*cmd_name;
	char	*cmd_path;
//	char	**argv;
	char	**envp;
	t_env	*env;
	t_cmd	*cmd;
};

struct s_cmd
{
	char	*cmd_path;
	char	**argv;
	t_cmd	*prev;
	t_cmd	*next;
};

struct s_token_type
{
	char	*type;
	int		id;
};

struct s_token
{
	struct s_token	*next;
	int				type;
	char			*content;
};

//------------------------------------------------------------------------------

//-Parser-----------------------------------------------------------------------
int		count_commands(t_token *token);
int		join_quotes(t_token *token);

void	dollar_format(t_token *token);
void	cat_word(t_token *token);

t_cmd	*parsing(char *input);
t_cmd	*command_set(t_token *token);

char	*_strjoin(char *s1, char *s2);
t_token	*get_tokens(char *input);

//tmp_tools.c
char	*token_type_print(int id);
void	free_cmd(t_cmd *cmd);
void	print_token_struct(t_token *token);
void	print_cmd_struct(t_cmd *cmd);
//------------------------------------------------------------------------------

//-Builtins---------------------------------------------------------------------
int		is_builtin(char *cmd_name);

void	exec_builtin(t_infos *infos, char *cmd_name);
void	builtin_export(t_infos *infos, t_cmd *cmd);
void	builtin_unset(t_infos *infos);
void	builtin_env(t_infos *infos);
void	builtin_echo(t_infos *infos);
void	builtin_cd(t_infos *infos);
void	builtin_pwd(void);
void	builtin_exit(t_infos *infos);
//------------------------------------------------------------------------------

//-Parsing----------------------------------------------------------------------
char	*get_command_path(char *cmd);
char	*get_cmd_name(char *line);
char	**get_command_args(char *line);
//------------------------------------------------------------------------------

//-Execution--------------------------------------------------------------------
void	exec_simple(t_infos *infos);
//------------------------------------------------------------------------------

//-Utils------------------------------------------------------------------------
int		exit_program(t_infos *infos, int exit_code, int started);
int		is_str_clear(char *str);
int		_strcmp(char *s1, char *s2);
int		varcmp(char *var1, char *var2);
int		is_var_in_env(t_env *env, char *var);

char	*get_env_var_value(t_infos *infos, char *var);
char	*fill_command_path(char *start_path, char *end_path);

void	free_char_tab(char **tab);
//--Env-&-Cp_env----------------------------------------------------------------
int		varcmp(char *env_var, char *var);

void	free_env(t_env *env);
void	add_env_var(t_infos *infos, char *var, int from_env);
void	remove_env_var(t_infos *infos, char *var);
void	cpy_env_to_lst(t_infos *infos, char **envp);
void	cpy_env_to_char(t_infos *infos);
void	set_pwd_var(t_infos *infos);
void	set_oldpwd_var(t_infos *infos);

t_env	*new_env_var(char *var, int from_env);
//------------------------------------------------------------------------------

//-Signals----------------------------------------------------------------------
void	handler(int signum);
//------------------------------------------------------------------------------

#endif
