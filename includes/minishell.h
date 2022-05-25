/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/25 16:52:59 by wdebotte         ###   ########.fr       */
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
	char	*variable;
	t_env	*next;
};

struct	s_infos
{
	char	*line;
//	char	**argv;
	t_env	*env;
};
//------------------------------------------------------------------------------

//-Builtins---------------------------------------------------------------------
int		is_builtin(char *command);
void	exec_builtin(t_infos *infos);
void	builtin_export(t_infos *infos, char **argv);
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
void	free_char_tab(char **tab);
//--Env-------------------------------------------------------------------------
void	free_env(t_env *env);
void	cpy_env(t_env **env, char **envp);
void	add_env_var(t_env *env, char *variable);
//------------------------------------------------------------------------------

//-Signals----------------------------------------------------------------------
void	handler(int signum);
//------------------------------------------------------------------------------

#endif
