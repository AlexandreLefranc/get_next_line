/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:30:29 by alefranc          #+#    #+#             */
/*   Updated: 2021/12/02 08:54:13 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 4

// Main function
char	*get_next_line(int fd);

// Secondary functions

// Helper functions
// size_t	ft_strlen(const char *s);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strdup(const char *s);
// size_t	ft_strlcat(char *dest, const char *src, size_t size);
// char	*ft_strjoin(char const *s1, char const *s2);


#endif
