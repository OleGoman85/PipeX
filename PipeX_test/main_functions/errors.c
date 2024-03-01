/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:51:31 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/01 12:09:37 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	main_errors(int error)
{
	if (error == 1)
	{
		perror("pipe creating failed");
		exit(1);
	}
	if (error == 2)
	{
		perror("fork creating failed");
		exit(2);
	}
	if (error == 3)
	{
		perror("incorrect number of arguments");
		exit(3);
	}
	if (error == 4)
	{
		perror("read failure");
		exit(4);
	}
	if (error == 5)
	{
		perror("creation failure");
		exit(5);
	}
}

void	path_errors(int error)
{
	if (error == 6)
	{
		perror("path creation failed");
		exit(6);
	}
	if (error == 7)
	{
		perror("path file not found : /\n");
		exit(7);
	}
	if (error == 8)
	{
		perror("Invalid command! :/\n");
		exit(8);
	}
	if (error == 9)
	{
		perror("px_calloc failed");
		exit(9);
	}
	if (error == 10)
	{
		perror("px_strlen failed");
		exit(10);
	}
}
