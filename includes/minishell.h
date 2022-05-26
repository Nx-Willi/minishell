/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/26 16:40:11 by wdebotte         ###   ########.fr       */
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

# define FALSE			0
# define TRUE			1
# define CTRL_C			2

//-Structures-------------------------------------------------------------------
typedef struct s_infos	t_infos;
typedef struct s_env	t_env;

struct s_env
{
	int		from_env;
	char	*variable;
	t_env	*next;
};

struct	s_infos
{
	char	*line;
	char	*cmd_name;
	char	*cmd_path;
	char	**argv;
	char	**envp;
	t_env	*env;
};
//------------------------------------------------------------------------------

//-Builtins---------------------------------------------------------------------
int		is_builtin(t_infos *infos);

void	exec_builtin(t_infos *infos);
void	builtin_export(t_infos *infos);
void	builtin_unset(t_infos *infos);
void	builtin_env(t_infos *infos);
//------------------------------------------------------------------------------

//-Execution--------------------------------------------------------------------
char	*get_command_path(char *cmd);
char	*get_cmd_name(char *line);
char	**get_command_args(char *line);

void	exec_simple(t_infos *infos);
//------------------------------------------------------------------------------

//-Utils------------------------------------------------------------------------
int		exit_program(int exit_code);
int		is_str_clear(char *str);
int		_strcmp(char *s1, char *s2);
int		varcmp(char *env_var, char *var);

void	free_char_tab(char **tab);
//--Env-&-Cp_env----------------------------------------------------------------
int		varcmp(char *env_var, char *var);

void	free_env(t_env *env);
void	add_env_var(t_infos *infos, char *var, int from_env);
void	remove_env_var(t_infos *infos, char *var);
void	cpy_env_to_lst(t_infos *infos, char **envp);
void	cpy_env_to_char(t_infos *infos);

t_env	*new_env_var(char *var, int from_env);
//------------------------------------------------------------------------------

//-Signals----------------------------------------------------------------------
void	handler(int signum);
//------------------------------------------------------------------------------

#endif
