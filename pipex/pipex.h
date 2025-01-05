#ifndef PIPEX_H
#define PIPEX_H


#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>


typedef struct card
{
    int infile;
    int outfile;
    int pipe[2];
    pid_t pid1;
    pid_t pid2;

}rabat;


char	*read_file(int fd, char *buffer, char **remainder);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    print_error(char *str, int flag);
void    first_child(rabat *card, char **av, char **env);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char    *find_path(char *cmd,char **env);
void    free_strings(char **str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif