/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:54 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/27 10:54:57 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	processes_making(t_data *data)
{
	if (pipe(data->fd) < 0)
		main_errors(1);
	data->pid = fork();
	if (data->pid < 0)
		main_errors(2);
	if (data->pid == 0) // child process
	{
		close(data->fd[0]); // close read end of pipe
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		process(data->av[1], data);
	}
	if (data->pid > 0)
	{
		wait(NULL);
		close(data->fd[1]); // close write end of pipe
		dup2(data->file_out, STDOUT_FILENO);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		process(data->av[2], data);
	}
}