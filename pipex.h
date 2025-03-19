/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:26:37 by obajali           #+#    #+#             */
/*   Updated: 2025/03/19 09:34:58 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct card
{
	int		infile;
	int		outfile;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;

}			t_rabat;

/*-------------[ String Manipulation Functions ]------------------*/
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/*-------------[ Memory Management Functions ]------------------*/
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);

/*-------------[ Utility Functions ]------------------*/
char		*find_path(char **cmd, char **env);
void		free_strings(char **str);
void		open_file(char *file, int flag, t_rabat *card);
void		print_error(char *str, char **alloc, int flag);

#endif