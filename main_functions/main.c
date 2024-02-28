/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:50:53 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/28 15:58:50 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipex.h"

// /*
// 	*Cheking amounts of arguments
// 	*Open files for read and write
// 	*Save files descriptors for in and out files
// 	*Save comand line arguments and environment variables
// */
// int	main(int ac, char **av, char **env)
// {
// 	t_data	data;

// 	if (ac == 5)
// 	{
// 		data.file_in = open(av[1], O_RDONLY);
// 		if (data.file_in < 0)
// 			main_errors(4);
// 		data.file_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
// 		if (data.file_out < 0)
// 			main_errors(5);
// 		data.av = &av[1];
// 		data.env = env;
// 		processes_making(&data);
// 	}
// 	else
// 		main_errors(3);
// 	return (0);
// }


#include "../pipex.h"
#include <string.h>

/*
	*Cheking amounts of arguments
	*Open files for read and write
	*Save files descriptors for in and out files
	*Save comand line arguments and environment variables
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac == 5)
	{
		if (strcmp(av[0] + 2, av[1]) == 0)
		{
			main_errors(4);
		}
		data.file_in = open(av[1], O_RDONLY);
		if (data.file_in < 0)
			main_errors(4);
		data.file_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data.file_out < 0)
			main_errors(5);
		data.av = &av[1];
		data.env = env;
		processes_making(&data);
	}
	else
		main_errors(3);
	return (0);
}