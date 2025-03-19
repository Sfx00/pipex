/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:21:02 by obajali           #+#    #+#             */
/*   Updated: 2025/03/19 09:06:22 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	execute_command(int input_fd, int output_fd, char *av, char **env)
{
	char	**cmd;
	char	*path; 

	if (dup2(input_fd, 0) == -1) 
		print_error(NULL, NULL, 1);
	if (dup2(output_fd, 1) == -1)
		print_error(NULL, NULL, 1);
	cmd = ft_split(av, ' ');
	if(!cmd)
		print_error(NULL, NULL, 1);
	if (!*cmd)
	{
		free_strings(cmd);
		write(2, " : command not found\n", 21);
		exit(127);
	}
	path = find_path(cmd, env);
	execve(path, cmd, env);
	free(path);
	print_error(cmd[0], cmd, 1);
}

void	second_child(t_rabat *card, char **av, char **env)
{
	open_file(av[4], 1, card);
	close(card->pipe[1]);
	execute_command(card->pipe[0], card->outfile, av[3], env);
}

void	first_child(t_rabat *card, char **av, char **env)
{
	open_file(av[1], 0, card);
	close(card->pipe[0]);
	execute_command(card->infile, card->pipe[1], av[2], env);
}

void	pipex(t_rabat *card, char **av, char **env)
{
	int	status;

	if (pipe(card->pipe) == -1)
		print_error(NULL, NULL, 1);
	card->pid1 = fork();
	if (card->pid1 < 0)
		print_error(NULL, NULL, 254);
	if (card->pid1 == 0)
		first_child(card, av, env);
	card->pid2 = fork();
	if (card->pid2 < 0)
		print_error(NULL, NULL, 254);
	if (card->pid2 == 0)
		second_child(card, av, env);
	close(card->pipe[0]);
	close(card->pipe[1]);
	waitpid(card->pid1, &status, 0);
	waitpid(card->pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(WTERMSIG(status));
}

int	main(int ac, char **av, char **env)
{
	t_rabat	card;

	if (ac != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		exit(1);
	}
	if (!env)
	{
		write(2, "Error empty Environment\n", 24);
		exit(1);
	}
	pipex(&card, av, env);
	return (0);
}
