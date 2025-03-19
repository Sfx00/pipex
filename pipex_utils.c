/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:32:23 by obajali           #+#    #+#             */
/*   Updated: 2025/03/19 09:57:14 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str, char **alloc, int flag)
{
	perror(str);
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

void	open_file(char *file, int flag, t_rabat *card)
{
	if (flag == 0)
	{
		if (access(file, R_OK) == -1)
			print_error(file, NULL, 1);
		else
			card->infile = open(file, O_RDONLY);
	}
	else
	{
		card->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (card->outfile == -1)
			print_error(file, NULL, 1);
	}
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
