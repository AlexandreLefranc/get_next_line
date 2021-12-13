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
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc((s1_len + s2_len + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	joined[0] = '\0';
	ft_strlcat(joined, s1, s1_len + s2_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	free(s1);
	s1 = NULL;
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (ft_strdup(""));
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc((len + 1) * sizeof(*dup));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// Input : save_prev is a pointer to a string containing at least 1 \n
// Description : Modify save_prev to a new string which is the right side
//				 of the initial string delimited by the first \n
// Return : A new string which is the left side of the initial string
//			delimited by the first \n
// Example : return_from_save_prev("Salut\nComment ca va?\nBien merci")
//			 return : "Salut\n"
//			 save_prev : "Comment ca va?\nBien merci"
// Warning : Crash if there is not \n
char	*return_from_save_prev(char	**save_prev)
{
	char	*save_tmp;
	char	*output;
	char	*ptr_newline;

	ptr_newline = ft_strchr(*save_prev, '\n');
	*ptr_newline = '\0';
	save_tmp = ft_strdup(ptr_newline + 1);
	if (save_tmp == NULL)
		return (NULL);
	output = ft_strjoin(*save_prev, "\n");
	*save_prev = save_tmp;
	return (output);
}

// void	get_next_line_part2(char **str, char **save_prev, int fd)
// {
// 	char	buffer[BUFFER_SIZE + 1];
// 	ssize_t	read_r;
//
// 	buffer[BUFFER_SIZE] = '\0';
// 	read_return = read(fd, buffer, BUFFER_SIZE);
// 	if (read_return == -1)
// 		return (-1);
// 	if (read_return == 0)
// 		;
// }

// Protect for incorrect fd and BUFFER_SIZE
// Check if a save from a previous call exists and if so, if there is a \n in.
// If yes call return_from_save_prev and return it.
//
// Otherwise, read BUFFER_SIZE bytes to buffer.
// Create str from save_prev
// While we didn't meet a \n and we didn't reach EOF
//     append str with buffer and read BUFFER_SIZE new bytes to buffer
//
char	*get_next_line(int fd)
{
	static char	*save_prev = NULL;
	char		buffer[BUFFER_SIZE + 1];
	char		*str;
	ssize_t		read_return;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (save_prev != NULL && ft_strchr(save_prev, '\n') != NULL)
		return (return_from_save_prev(&save_prev));
	buffer[BUFFER_SIZE] = '\0';
	read_return = read(fd, buffer, BUFFER_SIZE);
	str = ft_strdup(save_prev);
	// printf("str before loop : %s\n", str);
	// printf("buffer before loop : %s\n", buffer);
	while (ft_strchr(buffer, '\n') == NULL && read_return == BUFFER_SIZE)
	{
		str = ft_strjoin(str, buffer);
		printf("str in loop : %s\n", str);
		read_return = read(fd, buffer, BUFFER_SIZE);
	}
	save_prev = ft_strdup(buffer);
	printf("save_prev after loop : %s\n", save_prev);
	printf("save_prev ptr : %p\n", save_prev);
	printf("str after loop : %s\n", str);
	char *s2 = return_from_save_prev(&save_prev);
	printf("return of return_from_save_prev : %s", s2);
	fflush(stdout);
	// str = ft_strjoin(str, return_from_save_prev(&save_prev));
	printf("full str : %s\n", str);
	return (str);
}
