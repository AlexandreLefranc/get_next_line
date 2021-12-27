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
	int		fd = 0;
	char	*str;
	char	*sleep = "sleep 1";

	// char	buffer[17];
	// ssize_t	r = read(1000, buffer, 16);
	// printf("%zi\n", r);

	printf("\n\n----------------------\nFD1000\n----------------------\n\n");
	while ((str = get_next_line(1000)) != NULL)
	{
		printf("=================================>%s", str);fflush(stdout);
		free(str);
		system(sleep);
	}
	close(fd);

	printf("\n\n----------------------\nTEST1\n----------------------\n\n");
	fd = open("../files/test1.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("=================================>%s", str);fflush(stdout);
		free(str);
		system(sleep);
	}
	close(fd);

	printf("\n\n----------------------\nNO TRAILING NL\n----------------------\n\n");
	fd = open("../files/test_no_trailing_nl.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("=================================>%s", str);fflush(stdout);
		free(str);
		system(sleep);
	}
	close(fd);
	//
	// printf("\n\n----------------------\nEMPTY\n----------------------\n\n");
	// fd = open("../files/empty.txt", O_RDONLY);
	// while ((str = get_next_line(fd)) != NULL)
	// {
	// 	printf("=================================>%s", str);fflush(stdout);
	// 	free(str);
	// 	system(sleep);
	// }
	// close(fd);
}
