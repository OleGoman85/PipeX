/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:50:53 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/27 10:50:56 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	
	if (ac == 5)
	{
		data.file_in = open(av[1], O_RDONLY);
		if (data.file_in < 0)
			main_errors(4);
		data.file_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data.file_out < 0)
			main_errors(5);
		data.av = &av[1]; // comand line arguments
		data.env = env; // set environment
		processes_making(&data);
	}
	else
		main_errors(3);
	return (0);
}