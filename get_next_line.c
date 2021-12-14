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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc((s1_len + s2_len + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	ft_strlcat(joined, s1, s1_len + s2_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
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


char	*extract_line(char **save_prev)
{
	char	*ptr_nl;
	char	*extracted;
	char	*new_save_prev;
	size_t	left_len;

	ptr_nl = ft_strchr(*save_prev, '\n');
	if (ptr_nl == NULL)
		return (NULL);
	left_len = ptr_nl - *save_prev + 1;
	extracted = ft_substr(*save_prev, 0, left_len);
	if (extracted == NULL)
		return (NULL);
	new_save_prev = ft_substr(*save_prev, left_len, ft_strlen(ptr_nl + 1));
	if (new_save_prev == NULL)
		return (NULL);
	free (*save_prev);
	*save_prev = new_save_prev;
	return (extracted);
}

/*
Check inputs
If there is something in save_prev
	If there is a \n
		return leftside and save_prev = rightside
	else
		Add save_prev to str
		free save_prev et set it to NULL
while we didn't reach EOF
	If there is no \n in buffer
		Add buffer to str
	else
		Add leftside to str and copy rightside to save_prev
		break
return str
*/
char	*get_next_line(int fd)
{
	static char	*save_prev = NULL;
	char		*str;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = NULL;
	if (save_prev != NULL)
	{
		if (ft_strchr(save_prev, '\n') != NULL)
			return (extract_line(&save_prev));
		str = ft_strjoin(str, save_prev);
		free(save_prev);
		save_prev = NULL;
	}
	buffer[BUFFER_SIZE] = '\0';
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		if (ft_strchr(buffer, '\n') == NULL)
			str = ft_strjoin(str, buffer);
		else
		{
			save_prev = ft_substr(buffer, 0, ft_strlen(buffer));
			str = ft_strjoin(str, extract_line(&save_prev));
			break ;
		}
	}
	return (str);
}
