/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:43:14 by alefranc          #+#    #+#             */
/*   Updated: 2021/12/02 13:05:29 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	str[10];

	fd = open("test1.txt", O_RDONLY);
	read(fd, str, 9);
	printf("%s\n", str);
	read(fd, str, 9);
	printf("%s\n", str);
	/* while ((str = get_next_line(fd) != NULL)) */
	/* { */
	/* 	printf("%s\n", str) */
	/* } */
	close(fd);
}
