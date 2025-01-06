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