#include "pipex.h"

int open_file(char *file, int flag, rabat *card)
{
   
    if(flag == 0)
    {
        card->infile = open(file, O_RDONLY);
        if(card->infile == -1)
            print_error("Failed to open input file", 1);
        return (card->infile);
    }
    else
    {
        card->outfile = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if(card->outfile == -1)
                print_error("Failed to open output file", 1);
    }
    return(card->outfile);
}

void execute_command(int input_fd, int output_fd, char *av, char **env)
{
    char **cmd;
    char *path;

    if(dup2(input_fd, 0) == -1)
        print_error("Failed to dup input_fd", 1);
    if(dup2(output_fd, 1) == -1)
        print_error("Failed to dup output_fd", 1);
    cmd = ft_split(av,' ');
    if(!cmd)
        print_error("Failed to split command", 1);
    path = find_path(cmd[0], env);
    if(!path)
    {
        free_strings(cmd);
        print_error("Command not found in PATH", 127);
    }
    execve(path, cmd, env);
    free_strings(cmd);
    free(path);
    print_error("Command not found");
}

void second_child(rabat *card,char **av,char **env)
{
    open_file(av[4], 1, card);
    close(card->pipe[1]);
    execute_command(card->pipe[0], card->outfile, av[3], env);
}

void first_child(rabat *card,char **av,char **env)
{
    open_file(av[1], 0, card);
    close(card->pipe[0]);
    execute_command(card->infile, card->pipe[1], av[2], env);
}

void pipex(rabat *card,char **av,char **env)
{
    if(pipe(card->pipe) == -1)
        print_error("Failed to create pipe");
    card->pid1 = fork();
    if(card->pid1 < 0)
        print_error("faild to fork");
    if(card->pid1 == 0)
        first_child(card, av, env);
    card->pid2 = fork();
    if(card->pid2 < 0)
        print_error("faild to create a child");
    if(card->pid2 == 0)
        second_child(card, av, env);
    close(card->pipe[0]);
    close(card->pipe[1]);
    waitpid(card->pid1, NULL, 0);
    waitpid(card->pid2, NULL, 0);
}

int main(int ac, char **av, char **env)
{
    if(ac != 5)
        print_error("Usage: ./pipex file1 cmd1 cmd2 file2");
    if(!env)
        print_error("Error empty Environment");

    rabat card;
    pipex(&card,av,env);
    return 0;
}
