/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:32:23 by obajali           #+#    #+#             */
/*   Updated: 2025/02/06 00:29:34 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *file, char *str, char **alloc,int flag)
{
	if (file)
	{
		write(2, file, ft_strlen(file));
		write(1, ": ", 2);
	}
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
	if (alloc)
		free_strings(alloc);
	if(flag)
		exit(flag);
}

void	free_strings(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

char	*check_path(char **full_path, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (full_path[i])
	{
		tmp = ft_strjoin(full_path[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
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
			if(env[i][5] == '\0')
				print_error(NULL, "PATH is empty",cmd, 127);
			full_path = ft_split(env[i] + 5, ':');
			if (!full_path)
				return (NULL);
			path = check_path(full_path, cmd[0]);
			free_strings(full_path);
			if (!path)
				return (NULL);
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
	{
		if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
		return (NULL);
	}
	path = get_path(env, cmd);
	if (!path)
		return (NULL);
	return (path);
}
