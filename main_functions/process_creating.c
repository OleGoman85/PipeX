/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:54 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/28 11:48:07 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
/*
	child pid process = pid == 0
	parent pid process = pid > 0
	fd[0] = read = stdin = keyboard
	fd[1] = write = stdout = monitor
*/
void	processes_making(t_data *data)
{
	if (pipe(data->fd) < 0)
		main_errors(1);
	data->pid = fork();
	if (data->pid < 0)
		main_errors(2);
	if (data->pid == 0)
	{
		close(data->fd[0]);
		dup2(data->file_in, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		process(data->av[1], data);
	}
	if (data->pid > 0)
	{
		wait(NULL);
		close(data->fd[1]);
		dup2(data->file_out, STDOUT_FILENO);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		process(data->av[2], data);
	}
}
/*
	Creating processes using pipe and fork.
	Error checking during pipe and fork creation.
	# In the child process:
		Closing the read end of the pipe.
		Redirecting input to the input file and output to the pipe.
		Closing the write end of the pipe.
		Calling the process function with the first argument
			from the command line.
	# In the parent process:
		Waiting for the child process to finish.
		Closing the write end of the pipe.
		Redirecting output to the output file and input to the pipe.
		Closing the read end of the pipe.
		Calling the process function with the second argument from
			the command line.
*/