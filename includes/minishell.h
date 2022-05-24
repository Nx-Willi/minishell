/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/24 18:27:58 by wdebotte         ###   ########.fr       */
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

typedef struct s_infos	t_infos;
/*typedef struct s_env	t_env;

struct s_env
{
	char	*variable;
	t_env	*next;
};*/

struct	s_infos
{
	char	*line;
	t_list	*env;
};

//Builtins
int		is_builtin(char *command);

//Execution
char	*get_command_path(char *cmd);
char	**get_command_args(char *line);
void	exec_simple(t_infos *infos);

//Utils
int		exit_program(int exit_code);
void	free_char_tab(char **tab);
void	free_list(t_list *list);
void	get_env(t_list *env, char **envp);

//Signals
void	handler(int signum);

#endif
