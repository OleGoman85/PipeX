/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:54:54 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/11 07:06:24 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*create pipe, fork, wait waitpid status*/
void	processes_making(t_data *data)
{
	int	status;

	if (pipe(data->fd) < 0)
		main_errors(1);
	data->pid1 = fork();
	if (data->pid1 < 0)
		close_fd(data);
	if (data->pid1 == 0)
		child_pid1(data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		close_fd(data);
	if (data->pid2 == 0)
		child_pid2(data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, &status, 0);
	data->status = status;
}

/* open first file, redirecting input and output for each child process. */
void	child_pid1(t_data *data)
{
	data->file_in = open(data->av[0], O_RDONLY);
	if (data->file_in < 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		main_errors(4);
	}
	close(data->fd[0]);
	dup2(data->file_in, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->file_in);
	close(data->fd[1]);
	process(data->av[1], data);
}

/*open second file, redirecting output and input for each child process. */
void	child_pid2(t_data *data)
{
	data->file_out = open(data->av[3], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (data->file_out < 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		main_errors(5);
	}
	close(data->fd[1]);
	dup2(data->file_out, STDOUT_FILENO);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->file_out);
	close(data->fd[0]);
	process(data->av[2], data);
}

/*close pipes fd*/
void	close_fd(t_data *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	main_errors(2);
}

/*
	CHILD    pid process: pid == 0
	PARENT   pid process: pid > 0
	fd[0] = read = stdin = keyboard
	fd[1] = write = stdout = monitor
*/