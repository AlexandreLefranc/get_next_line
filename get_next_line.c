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

// clangc main.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=1

#include "get_next_line.h"

static int	format_cache(char **cache)
{
	if (*cache == NULL)
	{
		*cache = ft_strdup("");
		if (*cache == NULL)
			return (-1);
	}
	return (0);
}

static int	update_cache(char **cache)
{
	char	*new_cache;
	char	*ptr_nl;

	ptr_nl = ft_strchr(*cache, '\n');
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
	return (0);
}

static char	*extract_line(const char *cache)
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
static int	get_line(int fd, char **cache)
{
	char	buf[BUFFER_SIZE + 1];
	char	*new_cache;
	ssize_t	ret;

	ret = 1;
	while (ret != 0 && ft_strchr(*cache, '\n') == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free (*cache);
			*cache = NULL;
			return (-1);
		}
		if (ret == 0 && *cache[0] != '\0')
			return (0);
		buf[ret] = '\0';
		new_cache = ft_strjoin(*cache, buf);
		free(*cache);
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

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (format_cache(&cache[fd]) == -1)
		return (NULL);
	if (get_line(fd, &cache[fd]) == -1)
		return (NULL);
	line = extract_line(cache[fd]);
	if (line == NULL)
	{
		free(cache[fd]);
		cache[fd] = NULL;
		return (NULL);
	}
	if (update_cache(&cache[fd]) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
