/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:57:41 by wdebotte          #+#    #+#             */
/*   Updated: 2022/07/18 14:46:43 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PLUSEQUAL 3

extern int	g_exit_status;

static int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if ((i == 0 && !ft_isalpha(arg[i]))
			|| (arg[i] == '*' || arg[i] == '-'))
		{
			puterror(arg);
			return (FALSE);
		}
		i++;
	}
	if (i == 0)
	{
		puterror(arg);
		return (FALSE);
	}
	if (ft_strchr(arg, '=') == NULL)
		return (FALSE);
	if (arg[i] == '=' && arg[i - 1] == '+')
		return (PLUSEQUAL);
	return (TRUE);
}

static void	add_to_existing_var(t_infos *inf, char *arg)
{
	int			i;
	char		*var_value;
	char		*new_value;
	char		*new_variable;
	static char	var[] = "";

	var[0] = '\0';
	i = -1;
	while (arg[++i] != '\0' && arg[i] != '+')
		var[i] = arg[i];
	var[i] = '\0';
	var_value = get_env_var_value(inf, var);
	new_value = ft_strjoin(var_value, arg + ft_strlen(var) + 2);
	var[i++] = '=';
	var[i] = '\0';
	new_variable = ft_strjoin(var, new_value);
	add_env_var(inf, new_variable, FALSE);
	free(new_value);
	free(new_variable);
}

static int	add_var(t_cmd *cmd, char *arg)
{
	int	status;

	status = is_valid_identifier(arg);
	if (status == FALSE)
	{
		g_exit_status = FAILURE;
		return (FALSE);
	}
	else if (status == PLUSEQUAL)
		add_to_existing_var(cmd->infos, arg);
	else
		add_env_var(cmd->infos, arg, FALSE);
	g_exit_status = SUCCESS;
	return (TRUE);
}

void	builtin_export(t_cmd *cmd)
{
	int	i;
	int	new_var;

	new_var = FALSE;
	if (cmd->argv[1] == NULL)
	{
		print_env(cmd->infos->env);
		g_exit_status = SUCCESS;
		return ;
	}
	i = 0;
	while (cmd->argv[++i] != NULL)
	{
		if (add_var(cmd, cmd->argv[i]) == FALSE)
			continue ;
		else
			new_var = TRUE;
	}
	if (new_var == TRUE)
		cpy_env_to_char(cmd->infos);
}
