/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:50:53 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/12 08:36:47 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <string.h>

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac == 5)
	{
		if (px_strcmp(av[0] + 2, av[1]) == 0)
			main_errors(4);
		data.av = &av[1];
		data.env = env;
		processes_making(&data);
	}
	else
		main_errors(3);
	return (WEXITSTATUS(data.status));
}
