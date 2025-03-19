/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:43:25 by obajali           #+#    #+#             */
/*   Updated: 2025/03/19 09:43:56 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *join_path(char *full_path, char *cmd)
{
	char *tmp;
	char *path;
	
	tmp = ft_strjoin(full_path, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return(path);
}

char	*check_path(char **full_path, char **cmd)
{
	char	*path;
	char	*path_0;
	int		i;

	path_0 = NULL;
	i = 0;
	while (full_path[i])
	{
		path = join_path(full_path[i++], *cmd);
		if (!path)
		{
			free_strings(full_path);
			print_error(NULL, cmd, 1);
		}
		if (access(path, X_OK) == 0)
			return (free(path_0), path);
		else if (access(path, F_OK) == 0 && path_0 == NULL)
		{
			path_0 = path;
			path = NULL;
		}
		free(path);
	}
	return (path_0);
}

char	*get_path(char **env, char **cmd)
{
	int		i;
	char	**full_path;
	char	*path;

	i = 0;
	
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			full_path = ft_split(env[i] + 5, ':');
			if (!full_path)
				print_error(NULL, cmd, 1);
			path = check_path(full_path, cmd);
			free_strings(full_path);
			if (!path)
				return (NULL);// cmdnfound
			else
				return (path);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char **cmd, char **env)
{
	char	*path;

	if (ft_strchr(cmd[0], '/'))
		return (cmd[0]);
	path = get_path(env, cmd);
	if (!path)
	{
		write(2,cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		free_strings(cmd);
		exit(127);
	}
	return (path);
}