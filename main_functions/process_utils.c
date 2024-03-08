/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:52:32 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/08 09:07:45 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

// static void	get_path(t_data *data, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*path_line;
// 	char	*path;

// 	i = 0;
// 	j = 5;
// 	while (env[i] && px_strncmp(env[i], "PATH=", j))
// 		i++;
// 	if (!env[i])
// 		path = "";
// 	else
// 		path = env[i][j];
// 	// path_line = px_calloc(px_strlen(path) + 1, sizeof(char));
// 	// px_strlcpy(path_line, &env[i][j], px_strlen(&env[i][j]) + 1);
// 	data->path = px_split(path_line, ':');
// 	//if ! split -> error and stop
// }