/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:30:21 by alefranc          #+#    #+#             */
/*   Updated: 2021/12/02 13:05:23 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	output = ft_strdup(*save_prev);
	free(*save_prev);
	*save_prev = save_tmp;
	return (output);
}

// Create a new node with content
// Free content and set it to NULL
// Add the new node to the list
// void	ft_lstadd_back(t_list **alst, char **content)
// {
// 	t_list	*lst;
// 	t_list	*node;
//
// 	node = (t_list *)malloc(1 * sizeof(*node));
// 	if (node == NULL)
// 		return (NULL);
// 	node->content = *content;
// 	node->next = NULL;
// 	free(*content);
// 	*content = NULL;
// 	if (alst == NULL)
// 		return ;
// 	if (*alst == NULL)
// 	{
// 		*alst = node;
// 		return ;
// 	}
// 	lst = *alst;
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	lst->next = node;
// }

get_next_line_part2(t_list **lst, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
}

char	*get_next_line(int fd)
{
	static char	*save_prev = NULL;
	t_list		*lst;
	char		*str;

	if (save_prev != NULL && ft_strchr(save_prev, '\n') != NULL)
		return (return_from_save_prev(&save_prev));
	lst = NULL;
	ft_lstadd_back(&lst, &save_prev); // it should also free save_prev and set to NULL
	
}
