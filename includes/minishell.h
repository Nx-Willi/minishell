/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:45:25 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/21 15:30:22 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structures.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MSG_COLOR	"\e[1m\e[93m" 
# define BLANK		"\e[0m"
# define SH_NAME	MSG_COLOR"miniche"BLANK

# define FALSE		0
# define TRUE		1

# define CTRL_C		2
# define ULLLIMIT	9223372036854775807UL

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
	BACKSLASH,
};

enum	e_type_status
{
	SUCCESS = 0,
	FAILURE = 1,
	PARSING,
	BAD_PERMIT = 126,
	DOESNT_EXIST = 127,
	INTERRUPT = 127
};

//-Parser-----------------------------------------------------------------------
int		count_commands(t_token *token);
int		join_quotes(t_token *token);
int		check_syntax(t_token *token);
int		check_redir(t_token *token);

void	dollar_format(t_infos *infos, t_token *token);
void	cat_word(t_token *token);
void	add_id(t_cmd *cmd);
void	format_dollar_in_quote(t_token *token);

t_cmd	*parsing(t_infos *infos, char *input);
t_cmd	*command_set(t_infos *infos, t_token *token);

char	*_strjoin(char *s1, char *s2);
char	*get_command_path(t_infos *infos, char *cmd);

t_token	*get_tokens(char *input);
t_token	*ignore_white_space(t_token *token);
t_token	*redir(t_token *token, t_cmd *cmd);
t_token	*get_heredoc(t_token *token);

//tmp_tools.c
char	*token_type_print(int id);
void	print_token_struct(t_token *token);
void	print_cmd_struct(t_cmd *cmd);
//------------------------------------------------------------------------------

//-Builtins---------------------------------------------------------------------
int		is_builtin(char *cmd_name);

void	exec_builtin(t_cmd *cmd);
void	builtin_export(t_cmd *cmd);
void	print_env(t_env *env);
void	builtin_unset(t_cmd *cmd);
void	builtin_env(t_infos *infos);
void	builtin_echo(t_cmd *cmd);
void	builtin_cd(t_cmd *cmd);
void	builtin_pwd(t_infos *infos);
void	builtin_exit(t_cmd *cmd);
//------------------------------------------------------------------------------

//-Execution--------------------------------------------------------------------
void	exec_simple(t_cmd *cmd);
void	exec_pipes(t_infos *inf);
void	exec_commands(t_infos *infos);
void	exec_cmd(t_cmd *cmd);
void	do_redirections(t_cmd *cmd);
void	clean_redirections(t_cmd *cmd);
void	redir_builtin(t_cmd *cmd);
//--Utils
void	close_pipes(char *error, int **pfds, int idx_pipes, int idx_tab);
void	retwait_pids(t_infos *infos, int *pids);

int		**init_pipefds(int npipes);
//------------------------------------------------------------------------------

//-Utils------------------------------------------------------------------------
int		is_str_clear(char *str);
int		_strcmp(char *s1, char *s2);

void	free_char_tab(char **tab);
void	free_cmd(t_cmd *cmd);
void	exit_program(int exit_code);
void	puterror(t_cmd *cmd, char *arg, char *error);
void	print_message(void);

char	*fill_command_path(char *start_path, char *end_path);
//--Env-------------------------------------------------------------------------
int		is_var_in_env(t_env *env, char *var);
int		varcmp(char *var1, char *var2);

void	free_env(t_env *env);
void	add_env_var(t_infos *infos, char *var, int from_env);
void	remove_env_var(t_infos *infos, char *var);
void	cpy_env_to_lst(t_infos *infos, char **envp);
void	cpy_env_to_char(t_infos *infos);
void	set_pwd_var(t_infos *infos);
void	set_oldpwd_var(t_infos *infos, char *old_path);
void	set_shlvl_var(t_infos *infos);

char	*get_env_var_value(t_infos *infos, char *var);
t_env	*new_env_var(char *var, int from_env);
//------------------------------------------------------------------------------

//-Signals----------------------------------------------------------------------
void	handler(int signum);
//------------------------------------------------------------------------------

#endif
