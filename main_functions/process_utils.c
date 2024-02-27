/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:52:32 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/27 10:52:34 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	get_path(t_data *data, char **env)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 5;
	while (env[i] && px_strncmp(env[i], "PATH=", j))
		i++;
	if (!env[i])
		exit(2);
	ptr = px_calloc(px_strlen(&env[i][j]) + 1, sizeof(char));
	px_strlcpy(ptr, &env[i][j], px_strlen(&env[i][j]) + 1);
	data->path = px_split(ptr, ':');
}

void	process(char *command, t_data *data)
{
	int		i;
	char	*pth_cmd;
	char	*hold;
	
	i = 0;
	get_path(data, data->env);
	data->cmd_opt = px_split(command, ' ');
	while (data->path[i])
	{
		hold = px_strjoin("/", data->cmd_opt[0]);
		pth_cmd = px_strjoin(data->path[i], hold);
		if (!access(pth_cmd, F_OK))
		{
			if(!access(pth_cmd, X_OK))
				execve(pth_cmd, data->cmd_opt, data->env);
			else
				path_errors(7);
		}
		free(hold);
		free(pth_cmd);
		i++;
	}
	path_errors(8);
}

//     str = (char *) s;: Эта строка приводит указатель s к типу char * и присваивает его переменной str. Поскольку параметр s объявлен как char const *, он указывает на строку, которая не может быть изменена. Однако функция ft_alloc_all принимает аргумент типа char *, поэтому мы должны создать временную переменную str, чтобы мы могли изменять ее внутри функции ft_alloc_all, если это необходимо.

//     ptr = ft_calloc((ft_strcount(str, c) + 1), sizeof(char *));: Эта строка выделяет память под массив указателей ptr, который будет содержать разделенные подстроки. Размер массива вычисляется как количество подстрок плюс один (для завершающего нулевого указателя). Функция ft_strcount используется для подсчета количества подстрок в строке str, разделенных символом c.

//     ft_alloc_all(str, c, w, ptr);: Эта строка вызывает функцию ft_alloc_all, которая разбивает строку str на подстроки, используя разделитель c, и выделяет память для каждой из этих подстрок. Результаты помещаются в массив указателей ptr.

// Таким образом, эти три строки выполняют необходимые операции для разделения строки s на подстроки, используя символ c в качестве разделителя, и возвращают массив указателей на эти подстроки.

// ft_alloc_all(str, c, w, ptr);
// str - stroka PATHA= (a tochnej, vse chto pozle)
// ptr - massiv ukazatelej, kuda budut zapisani rzdelennie stroki(poka pustoj)
// c - ':'