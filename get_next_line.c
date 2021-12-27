/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:30:21 by alefranc          #+#    #+#             */
/*   Updated: 2021/12/13 12:30:50 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// clangc main.c ../get_next_line.c -D BUFFER_SIZE=1 && ./a.out

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	c2;
	size_t	i;

	c2 = (char)c;
	ptr = (char *)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == c2)
			return (&ptr[i]);
		i++;
	}
	if (ptr[i] == c2)
		return (&ptr[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		sub = malloc(1 * sizeof(*sub));
	else if (len > ft_strlen(s) - start)
		sub = malloc((ft_strlen(s) - start + 1) * sizeof(*sub));
	else
		sub = malloc((len + 1) * sizeof(*sub));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[i + start] != '\0' && i < len && start < ft_strlen(s))
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(char const *s)
{
	char	*dup;

	dup = ft_substr(s, 0, ft_strlen(s));
	if (dup == NULL)
		return (NULL);
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		joined[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined[j] = s2[i];
		i++;
		j++;
	}
	joined[j] = '\0';
	return (joined);
}

int	format_cache(char **cache)
{
	if (*cache == NULL)
	{
		*cache = ft_strdup("");
		if (*cache == NULL)
			return (-1);
	}
	return (0);
}


int	update_cache(char **cache)
{
	char	*new_cache;
	char	*ptr_nl;

	// printf("Begining of update_cache : %s\n", *cache);
	ptr_nl = ft_strchr(*cache, '\n');
	// printf("Begining of update_cache : %p\n", ptr_nl);
	if (ptr_nl == NULL)
	{
		free(*cache);
		*cache = NULL;
		return (0);
	}
	else
		new_cache = ft_strdup(ptr_nl + 1);
	free(*cache);
	*cache = NULL;
	if (new_cache == NULL)
		return (-1);
	*cache = new_cache;
	// printf("End of update_cache, *cache = %s\n", *cache);
	return (0);
}

char	*extract_line(const char *cache)
{
	char	*line;
	char	*ptr_nl;

	if (cache == NULL)
		return (NULL);
	ptr_nl = ft_strchr(cache, '\n');
	if (ptr_nl == NULL)
		line = ft_strdup(cache);
	else
		line = ft_substr(cache, 0, ptr_nl - cache + 1);
	if (line == NULL)
		return (NULL);
	// printf("line in extract_line : %s\n", line);
	if (line[0] == '\0')
	{
		free (line);
		line = NULL;
	}
	return (line);
}

// Set *cache to a string containing at least 1 \n.
// The \n is not necessary at the end.
// Should set *cache to NULL if nothing is read.
// Should set *cache to NULL if ret == 0 and *cache == ""
int	get_line(int fd, char **cache)
{
	char	buf[BUFFER_SIZE + 1];
	char	*new_cache;
	ssize_t	ret;

	ret = 1;
	while (ret != 0 && ft_strchr(*cache, '\n') == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		// printf("ret in get_line : %zu\n", ret);
		if (ret == -1)
		{
			free (*cache);
			*cache = NULL;
			return (-1);
		}
		// printf("Stop condition in get_line : %d\n", ret == 0 && *cache[0] != '\0');
		if (ret == 0 && *cache[0] != '\0')
			return (0);
		buf[ret] = '\0';
		new_cache = ft_strjoin(*cache, buf);
		// printf("new_cache in get_line : %s\n", new_cache);
		// free(*cache);
		*cache = NULL;
		if (new_cache == NULL)
			return (-1);
		*cache = new_cache;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*cache[1024];
	char		*line;
	int			check;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	// printf("cache before format_cache : %s\n", cache[fd]);
	check = format_cache(&cache[fd]);
	// printf("cache after format_cache : %s\n", cache[fd]);
	if (check == -1)
		return (NULL);
	check = get_line(fd, &cache[fd]);
	// printf("cache after get_line : %s\n", cache[fd]);
	if (check == -1)
		return (NULL);
	line = extract_line(cache[fd]);
	// printf("line after extract : %s\n", line);
	if (line == NULL)
	{
		free(cache[fd]);
		cache[fd] = NULL;
		return (NULL);
	}
	// printf("Before update_cache : %s\n", cache[fd]);
	check = update_cache(&cache[fd]);
	// printf("After update_cache : %s\n", cache[fd]);
	if (check == -1)
	{
		printf("In error update_cache\n");
		free(line);
		return (NULL);
	}
	return (line);
}

/*
LES DIFFERENTS CAS A PENSER
1 - Cas ou buffer contient tout le fichier
	a - Terminé par \n
	b - Non terminé par \n
2 - Cas ou buffer prend 1 caractere a la fois
	a - Terminé par \n
	b - Non terminé par \n
3 - Cas ou buffer prends le nombre de caractere de la ligne
*/
