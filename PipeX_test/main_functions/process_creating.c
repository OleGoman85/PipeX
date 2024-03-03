/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:54 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/02 13:12:19 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
/*
	CHILD    pid process: pid == 0
	PARENT   pid process: pid > 0
	fd[0] = read = stdin = keyboard
	fd[1] = write = stdout = monitor
*/

void	processes_making(t_data *data)
{
	int	status;

	if (pipe(data->fd) < 0)
	{
		close(data->file_in);
		close(data->file_out);
		main_errors(1);
	}
	data->pid1 = fork();
	if (data->pid1 < 0)
		close_all(data);
	if (data->pid1 == 0)
		child_pid1(data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		close_all(data);
	if (data->pid2 == 0)
		child_pid2(data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &status, 0);
	data->status = status;
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

void	child_pid1(t_data *data)
{
	close(data->fd[0]);
	dup2(data->file_in, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	process(data->av[1], data);
}

void	child_pid2(t_data *data)
{
	close(data->fd[1]);
	dup2(data->file_out, STDOUT_FILENO);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
	process(data->av[2], data);
}

void	close_all(t_data *data)
{
	close(data->file_in);
	close(data->file_out);
	close(data->fd[0]);
	close(data->fd[1]);
	main_errors(2);
}

// void	processes_making(t_data *data)
// {
// 	if (pipe(data->fd) < 0)
// 		main_errors(1);
// 	data->pid1 = fork();
// 	if (data->pid1 < 0)
// 		main_errors(2);
// 	if (data->pid1 == 0)
// 	{
// 		// close(data->fd[0]);
// 		// dup2(data->file_in, STDIN_FILENO);
// 		// dup2(data->fd[1], STDOUT_FILENO);
// 		// close(data->fd[1]);
// 		// process(data->av[1], data);
// 		child_pid1(data);
// 	}
// 	data->pid2 = fork();
// 	if (data->pid2 < 0)
// 		main_errors(2);
// 	if (data->pid2 == 0)
// 	{
// 		// close(data->fd[1]);
// 		// dup2(data->file_out, STDOUT_FILENO);
// 		// dup2(data->fd[0], STDIN_FILENO);
// 		// close(data->fd[0]);
// 		// process(data->av[2], data);
// 		child_pid2(data);
// 	}
// 	printf("wait pid1\n");
// 	waitpid(data->pid1, NULL, 0);
// 	printf("pid1 ready\n");
// 	printf("wait pid2\n");
// 	waitpid(data->pid2, NULL, 0);
// 	printf("pid2 ready\n");
// }