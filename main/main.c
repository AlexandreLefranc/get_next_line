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

	fd = open("../test1.txt", O_RDONLY);
	printf("FD = %d\n", fd);
	fflush(stdout);

	str = get_next_line(fd);
	printf("=================>Main : %s\n", str);

	str = get_next_line(fd);
	printf("=================>Main : %s\n", str);

	str = get_next_line(fd);
	printf("=================>Main : %s\n", str);

	str = get_next_line(fd);
	printf("=================>Main : %s\n", str);

	str = get_next_line(fd);
	printf("=================>Main : %s\n", str);
	// while ((str = get_next_line(fd)) != NULL)
	// {
	// 	printf("In main : %s\n\n", str);
	// 	fflush(stdout);
	// }
	close(fd);
}
