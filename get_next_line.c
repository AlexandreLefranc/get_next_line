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

char	*get_next_line(int fd)
{
	static char	*save_prev = NULL;
	char		*str;
	char		buffer[BUFFER_SIZE + 1];

	if (/*Check inputs*/)
		// Protect every that need protection
	if (save_prev != NULL); // If not first call
		// directement afficher si il y a un \n ou ajouter a str sinon
		// Modifier save_prev
	while (/*Didnt reach EOF, ie read > 0*/)
	{
		if (/*There is no \n in buffer*/);
			// Add buffer to str
		else;
			// Add left side to str
			// Copy the right side to save_prev
	}
	return (str);
}
