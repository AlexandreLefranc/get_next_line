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

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc((s1_len + s2_len + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	ft_strlcat(joined, s1, s1_len + s2_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
}


char	*get_next_line(int fd)
{
	ssize_t		read_len;
	char		*str;
	char		buffer[BUFFER_SIZE + 1];
	static char	*cache[MAX_FD];

	char		*ptr_tmp;

	str = ft_substr("", 0, 1);
	while ((read_len = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_len] = '\0';
		ptr_tmp = str;
		str = ft_strjoin(str, buffer);
		free(ptr_tmp);
		ptr_tmp = NULL;
		if (ft_strchr(str, '\n') != NULL)
		{
			ptr_tmp = str;
			cache[fd] = ft_substr(ptr_tmp, (ft_strchr(ptr_tmp, '\n') - ptr_tmp + 1), ft_strlen(ptr_tmp));
			str = ft_substr(ptr_tmp, 0, (ft_strchr(ptr_tmp, '\n') - ptr_tmp));
			free(ptr_tmp);
			ptr_tmp = NULL;
			return (str);
		}
	}
	if (ft_strchr(cache[fd], '\n') != NULL)
	{
		ptr_tmp = cache[fd];
		cache[fd] = ft_substr(ptr_tmp, (ft_strchr(ptr_tmp, '\n') - ptr_tmp + 1), ft_strlen(ptr_tmp));
		str = ft_substr(ptr_tmp, 0, (ft_strchr(ptr_tmp, '\n') - ptr_tmp));
		free(ptr_tmp);
		ptr_tmp = NULL;
		return (str);
	}
	else if (ft_strlen(cache[fd]) > 0)
	{
		str = cache[fd];
		cache[fd] = ft_substr("", 0, 1);
		return (str);
	}
	else
	{
		free(cache[fd]);
		cache[fd] = NULL;
		return (NULL);
	}
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

/*
Declare ssize_t read_len;
Declare char *str
Declare char *buffer
Init static char *cache[FD_MAX]

str = substr("", 0, 1)
Tant que (read_len = je lis quelque chose)
	str = strjoin(str, buffer)
	Si str contient \n
		sauvegarder la partie droite dans cache[fd]
		str = la partie gauche de str
		return str
Si cache[fd] contient \n
	sauvegarder la partie droite dans cache[fd]
	str = la partie gauche de cache[fd]
	return str
Sinon si len(cache[fd]) > 0
	str = cache[fd]
	return str
Sinon
	free cache[fd]
	return NULL
*/
