/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:45:54 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/17 16:31:30 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_infos		t_infos;
typedef struct s_env		t_env;
typedef struct s_token_type	t_token_type;
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
	int		npipes;
	char	*prompt;
	char	**envp;
	t_env	*env;
	t_cmd	*cmd;
};

struct s_cmd
{
	int		id;
	int		fd_in;
	int		fdin_tmp;
	int		fd_out;
	int		fdout_tmp;
	char	*cmd_path;
	char	**argv;
	t_cmd	*prev;
	t_cmd	*next;
	t_infos	*infos;
};

struct s_token_type
{
	char	*type;
	int		id;
};

struct s_token
{
	int		type;
	char	*content;
	t_token	*next;
};

#endif
