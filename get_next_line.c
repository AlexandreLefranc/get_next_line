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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	if (s == NULL)
		return (ft_strdup(""));
	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(*dup));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < (ft_strlen(s) + 1))
	{
		dup[i] = '\0';
		i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	j = size;
	while (*dest != '\0')
	{
		dest++;
		if (j > 0)
			j--;
	}
	while (*src != '\0' && j > 1)
	{
		*dest++ = *src++;
		j--;
	}
	*dest = '\0';
	if (size > dst_len)
		return (dst_len + src_len);
	return (size + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc((s1_len + s2_len + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (i < (s1_len + s2_len + 1))
	{
		joined[i] = '\0';
		i++;
	}
	ft_strlcat(joined, s1, s1_len + s2_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
}

// Change save_prev to what is on the right of \n
// return what is on the left of \n
// Need to free old *save_prev
char	*process_save_prev(char **save_prev)
{
	char	*ptr;
	char	*r;

	ptr = ft_strchr(*save_prev, '\n');
	*ptr = '\0';
	r = ft_strdup(*save_prev);
	*save_prev = ft_strdup(ptr + 1);
	return (r);
}

// char	*process_terminate(char **save_prev, char *buffer)
// {
//
// 	return (NULL);
// }

char	*get_next_line(int fd)
{
	static char	*save_prev = NULL;
	char		*str;
	char		buffer[BUFFER_SIZE + 1];

	//printf("Start of GNL\n");fflush(stdout);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	//printf("  save_prev : %s\n", save_prev);fflush(stdout);
	if (save_prev != NULL && ft_strchr(save_prev, '\n') != NULL)
		return(process_save_prev(&save_prev));
	str = ft_strdup(save_prev);
	//printf("  str : %s\n", str);fflush(stdout);
	buffer[BUFFER_SIZE] = '\0';
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		//printf("  str in Loop : %s\n", str);fflush(stdout);
		if (ft_strchr(buffer, '\n') != NULL)
		{
			save_prev = ft_strdup(buffer);
			str = ft_strjoin(str, process_save_prev(&save_prev));
			//printf("End1 of GNL\n");fflush(stdout);
			return (ft_strjoin(str, "\n"));
		}
		str = ft_strjoin(str, buffer);
	}
	//save_prev = ft_strdup(buffer);
	//printf("End2 of GNL\n");fflush(stdout);
	//return(process_terminate(&save_prev));
	return (str);
}
