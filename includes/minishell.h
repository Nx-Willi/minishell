/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-baux <xle-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:53:23 by wdebotte          #+#    #+#             */
/*   Updated: 2022/06/07 13:13:44 by xle-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

//# define CMD "ls -la | \"grep $TESTENVS\"h f"
//# define CMD "/sbin/ifconfig | grep 'inet ' | awk '{if(NR==1) print 2}'"
//# define CMD "\"cat $TESTENV\""
# define CMD "lsblk | grep \"lvm\" | \"wc -l\" >> test.txt"

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

typedef struct s_token_type
{
	char	*type;
	int		id;
}			t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	int				type;
	char			*content;
}					t_token;

typedef struct s_cmd
{
	char			*args;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;



/****************************************************************************/
/* 									 PARSER									*/				
/****************************************************************************/

//	parcer.c
int parsing(char *input);

//	token_lexer.c
t_token *get_tokens(char *input);

//	quotes_format.c
int join_quotes(t_token *token);

//	dollar_format.c
void dollar_format(t_token *token);

//	cat_word.c
void	cat_word(t_token *token);

//	tools.c
char	*_strjoin(char *s1, char *s2);
int		count_commands(t_token *token);

#endif
