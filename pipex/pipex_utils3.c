/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:29:04 by obajali           #+#    #+#             */
/*   Updated: 2025/01/07 15:37:42 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = ft_strdup("");
		return (p);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = ft_strlen((char *)s);
	p = (char *)malloc(sizeof(char) * len + 1);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	check_file(char *file)
{
	int	fd;

	if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
	{
		return (-1);
	}
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

void	open_file(char *file, int flag, t_rabat *card)
{
	int	dummy_pipe[2];

	if (flag == 0)
	{
		if (access(file, F_OK) == -1)
		{
			(pipe(dummy_pipe), close(dummy_pipe[1]));
			write(2, "No such file or directory\n", 26);
			card->infile = dummy_pipe[0];
		}
		else if (access(file, R_OK) == -1)
		{
			(pipe(dummy_pipe), close(dummy_pipe[1]));
			write(2, "Permission denied\n", 18);
			card->infile = dummy_pipe[0];
		}
		else
			card->infile = open(file, O_RDONLY);
	}
	else
	{
		card->outfile = check_file(file);
		if (card->outfile == -1)
			print_error(NULL, "Permission denied", 1);
	}
}
