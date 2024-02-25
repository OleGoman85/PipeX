/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:46:32 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/25 10:55:26 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void processes_making(t_data *data)
{
	char	*command1;
	char	*command2;
	
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
		command1 = data->av[1];
		process(command1, data);
	}
	else // parent process
	{
		wait(NULL);
		close(data->fd[1]); // close write end of pipe
		dup2(data->file_out, STDOUT_FILENO);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		command2 = data->av[2];
		process(command2, data);
	}
}

// data->file_in используется внутри функции processes_making,
// потому что переменная data передается в функцию как указатель
// (t_data *data). Используя оператор ->, мы получаем доступ к полю
// file_in структуры, на которую указывает указатель data.

// В случае data.file_in, это использование предполагает, 
// что переменная data является самой структурой t_data, а
// не указателем на нее. В функции main, когда мы создаем
// переменную data, она является просто экземпляром структуры t_data,
// а не указателем. Поэтому мы используем оператор . для доступа
// к полю file_in напрямую из структуры data.

// нужно закрыть data->fd[1] в дочернем процессе после его перенаправления в STDOUT_FILENO, чтобы избежать утечек файловых дескрипторов.