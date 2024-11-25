
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		lens1;
	int		i;
	char	*dup;

	lens1 = ft_strlen(s1);
	i = 0;
	dup = (char *)malloc(lens1 + 1);
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lendest;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (lensrc);
	lendest = ft_strlen(dst);
	i = 0;
	if (dstsize <= lendest)
		return (dstsize + lensrc);
	while (i < lensrc && lendest + i + 1 < dstsize)
	{
		dst[lendest + i] = src[i];
		i++;
	}
	dst[lendest + i] = '\0';
	return (lendest + lensrc);
}

char	*ft_strchr(const char *s, int c)
{
	char	char_find;

	char_find = (char)c;
	while (*s)
	{
		if (*s == char_find)
			return ((char *)s);
		s++;
	}
	if (char_find == '\0')
		return ((char *)s);
	return (NULL);
}
