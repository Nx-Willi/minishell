/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:35:36 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/19 18:54:20 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_in_dir(char *command, char *dir_name, int res)
{
	DIR				*fd_dir;
	struct dirent	*dir;

	if (command == NULL || dir_name == NULL)
		return (FALSE);
	fd_dir = opendir(dir_name);
	if (fd_dir == NULL)
		return (FALSE);
	while (1)
	{
		dir = readdir(fd_dir);
		if (dir == NULL)
			break ;
		if (ft_strlen(dir->d_name) > ft_strlen(command))
			res = ft_strncmp(dir->d_name, command, ft_strlen(dir->d_name));
		else
			res = ft_strncmp(dir->d_name, command, ft_strlen(command));
		if (res == 0)
		{
			closedir(fd_dir);
			return (TRUE);
		}
	}
	closedir(fd_dir);
	return (FALSE);
}

char	*fill_command_path(char *path, char *command)
{
	int		i;
	int		n;
	char	*buffer;

	buffer = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(command) + 2));
	if (buffer == NULL)
		return (NULL);
	i = -1;
	while (path[++i] != '\0')
		buffer[i] = path[i];
	buffer[i++] = '/';
	n = i;
	i = -1;
	while (command[++i] != '\0')
		buffer[n + i] = command[i];
	buffer[n + i] = '\0';
	return (buffer);
}

char	*get_command_path(char *command)
{
	int		i;
	char	**path_dir;
	char	*path_env;
	char	*path;

	path = NULL;
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path_dir = ft_split(path_env, ':');
	if (path_dir == NULL)
		return (NULL);
	i = 0;
	while (path_dir[i] != NULL)
	{
		if (is_command_in_dir(command, path_dir[i], 1))
		{
			path = fill_command_path(path_dir[i], command);
			free_char_tab(path_dir);
			return (path);
		}
		i++;
	}
	free_char_tab(path_dir);
	return (path);
}
