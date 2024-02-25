/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 07:20:08 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/25 10:36:07 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "pipex.h"
 

void	get_path(t_data *data, char **env)
{
	int		i;
	int		j;
	char	*myPath;

	i = 0;
	j = 5;
	while (env[i] && path_strncmp(env[i], "PATH=", j))
		i++;
	if (env[i] == NULL)
		path_errors(6); 
	myPath = px_calloc(px_strlen(&env[i][j]) + 1, sizeof(char));
	px_strlcpy(myPath, &env[i][j], px_strlen(&env[i][j]) + 1);
	data->path = px_split(myPath, ':');
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


// Например, если data->cmd_opt[0] содержит "cat", и data->path[i] содержит "/usr/bin", то после выполнения строки hold = ft_strjoin("/", data->cmd_opt[0]); переменная hold будет равна "/cat", и после выполнения строки pth_cmd = ft_strjoin(data->path[i], hold); переменная pth_cmd будет равна "/usr/bin/cat".

//execve(pth_cmd, data->cmd_opt, data->env);
// pth_cmd: путь к исполняемому файлу.
// data->cmd_opt: массив строк, представляющих аргументы для новой программы. Первый аргумент должен быть именем программы.
// data->env: массив строк, представляющих переменные окружения для новой программы.