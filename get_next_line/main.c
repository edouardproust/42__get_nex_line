/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:00:35 by eproust           #+#    #+#             */
/*   Updated: 2024/10/22 18:43:45 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
//	int		i;
	char	*next_line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		printf("Error opening the file.");
	if (fd < 0)
		return (1);
/*	i = 1;
	next_line = "";
	while (next_line)
	{ */
	next_line = get_next_line(fd);
	if (!next_line)
		return (1);
	printf("1:%s", next_line);
	free(next_line);
	next_line = get_next_line(fd);
	if (!next_line)
		return (1);
	printf("2:%s", next_line);
	free(next_line);
	next_line = get_next_line(fd);
	if (!next_line)
		return (1);
	printf("3:%s", next_line);
	free(next_line);
	/*		i++;
			}
	 */	close(fd);
	return (0);
}

