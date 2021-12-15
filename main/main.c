/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:43:14 by alefranc          #+#    #+#             */
/*   Updated: 2021/12/13 12:30:47 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


int	main()
{
	int		fd;
	char	*str;

	fd = open("../files/test1.txt", O_RDONLY);
	//fd = open("../files/test_no_trailing_nl.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("===========>%s\n\n", str);fflush(stdout);
		free(str);
	}
	close(fd);
}
