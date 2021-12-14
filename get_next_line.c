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

	if (fd < 0 || BUFFER_SIZE < 1);
		return (NULL);
	str = NULL;
	if (save_prev != NULL); // If there is something in save_prev
	{
		if (ft_strchr(save_prev, '\n') != '\n')
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
