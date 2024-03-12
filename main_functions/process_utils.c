/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:52:32 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/11 07:09:48 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*Get_path: Extracts the PATH environment variable and splits it into
													individual directories.*/
static void	get_path(t_data *data, char **env)
{
	int		i;
	char	*path_value;

	i = 0;
	while (env[i])
	{
		if (px_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_value = env[i] + 5;
			data->path = px_split(path_value, ':');
			if (data->path == NULL)
				path_errors(6);
			return ;
		}
		i++;
	}
	data->path = NULL;
}

/*process: Executes the specified command by searching for its executable path
				in the directories listed in the PATH environment variable.*/
void	process(char *command, t_data *data)
{
	int		i;
	char	*pth_cmd;
	char	*slash_command;

	i = 0;
	get_path(data, data->env);
	data->cmd_opt = px_split(command, ' ');
	if (data->cmd_opt == NULL)
		path_errors(9);
	while (data->path[i])
	{
		slash_command = px_strjoin("/", data->cmd_opt[0]);
		pth_cmd = px_strjoin(data->path[i], slash_command);
		if (access(pth_cmd, F_OK) == 0)
		{
			if (access(pth_cmd, X_OK) == 0)
				execve(pth_cmd, data->cmd_opt, data->env);
			path_errors(7);
		}
		i++;
		free(slash_command);
		free(pth_cmd);
	}
	path_errors(8);
}
