/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/20 14:23:53 by wdebotte         ###   ########.fr       */
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

# define FALSE	0
# define TRUE	1

//Builtins
int		is_builtin(char *command);

//Execution
char	*get_command_path(char *cmd);
char	**get_command_args(char *line, char *cmd);
void	exec_simple(char *cmd, char **argv);

//Utils
void	free_char_tab(char **tab);

#endif
