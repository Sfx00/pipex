/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajali <obajali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:11:23 by obajali           #+#    #+#             */
/*   Updated: 2025/03/19 08:30:22 by obajali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*free_word(char **s, int word)
{
	int	i;

	i = 0;
	while (i < word)
	{
		if (s[i] != NULL)
			free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	lenw(const char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (s == NULL)
		return (len);
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*create(const char *s, int i, char c)
{
	char	*p;
	int		x;

	x = 0;
	if (s == NULL)
		return (NULL);
	p = (char *)malloc((lenw(s + i, c) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		p[x++] = s[i++];
	}
	p[x] = '\0';
	return (p);
}

static int	counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (count);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		arr[2];

	arr[0] = 0;
	arr[1] = 0;

	p = (char **)ft_calloc((counter(s, c) + 1), sizeof(char *));
	if (p == NULL)
		return (NULL);
	while (s[arr[0]] != '\0')
	{
		while (s[arr[0]] == c && s[arr[0]] != '\0')
			arr[0]++;
		if (s[arr[0]] != '\0')
		{
			p[arr[1]] = create(s, arr[0], c);
			if (!p[arr[1]])
				return (free_word(p, arr[1]));
			arr[1]++;
		}
		while (s[arr[0]] != c && s[arr[0]] != '\0')
			arr[0]++;
	}
	p[arr[1]] = NULL;
	return (p);
}
  