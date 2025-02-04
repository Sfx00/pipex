/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:38:18 by obajali           #+#    #+#             */
/*   Updated: 2025/01/18 19:08:55 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_error(char *file, char *str)
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
}


int	create_pipe(t_rabat *card)
{
	if (pipe(card->pipe) == -1)
		print_error(NULL, "Failed to create pipe", 1);
	close (card->pipe[1]);
	return(card->pipe[0]);
}


int open_files_doc(char *file)
{
	int fd;
	if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
	{
		write_error(file,"Permission denied");
		exit(1);
	}
	if(access(file, F_OK) != -1)
		fd = open(file, O_WRONLY | O_APPEND);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}