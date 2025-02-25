/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:25:08 by obajali           #+#    #+#             */
/*   Updated: 2025/02/25 19:23:28 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char *file,t_rabat *card, int flag)
{
	int	fd;

	if (flag == 0)
	{
		if (access(file, F_OK) == -1)
		{
			write_error(file, "No such file or directory\n");
			return(create_pipe(card));
		}
		else if (access(file, R_OK) == -1)
		{
			write(2, "Permission denied\n", 18);
			return(create_pipe(card));
		}
		fd = open(file, O_RDONLY);
		
	}
	else
	{
		fd = check_file(file);
		if (fd == -1)
			print_error(NULL, "Permission denied",NULL, 1);
	}
	return (fd);
}

void	execute(char *argv, char **env)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		print_error(NULL, "Failed to split command",NULL, 1);
	path = find_path(cmd, env);
	if (!path)
		print_error(NULL, "Not found PATH of command",cmd, 127);
	execve(path, cmd, env);
	free(path);
	print_error(NULL, "Command not found",cmd, 127);
}

void	pipex(char *cmd,t_rabat *card, char **env)
{
	int	pid;
	
	if (pipe(card->pipe) == -1)
		print_error(NULL, "Failed to create pipe",NULL, 1);
	pid = fork();
	if (pid < 0)
		print_error(NULL, "faild to fork",NULL, 1);
	if (pid)
	{
		close(card->pipe[1]);
		dup2(card->pipe[0], 0);
		close(card->pipe[0]);
	}
	else
	{
		close(card->pipe[0]);
		dup2(card->pipe[1], 1);
		execute(cmd, env);
	}
}

void	handle_here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		print_error(NULL, "Pipe error",NULL, 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}
void	last_step(t_rabat *card,char *cmd,char **env)
{
	int state;
	int exit_status = 0;
	int	pid;
	
	pid = fork();
	if(pid == 0)
	{
		dup2(card->outfile,1);
		execute(cmd, env);
	}
	close(0);
	while (wait(&state) != -1)
	{
		if (WIFEXITED(state))
			exit_status = WEXITSTATUS(state);
	}
	exit(exit_status);
}


int	main(int ac, char **av, char **env)
{
	t_rabat	card;
	int		i;

	if (!env || ac < 5)
		print_error(NULL, "Error: Invalid arguments",NULL, 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			print_error(NULL, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 file",NULL,1);
		handle_here_doc(av[2]);
		card.outfile = open_files_doc(av[ac - 1]);
		i = 3;
	}
	else
	{
		card.infile = open_files(av[1],&card, 0);
		card.outfile = open_files(av[ac - 1], &card, 1);
		dup2(card.infile, 0);
		i = 2;
	}
	while (i < ac - 2)
		pipex(av[i++],&card,env);
	last_step(&card,av[i],env);
}

