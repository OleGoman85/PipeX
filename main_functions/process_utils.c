/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:52:32 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/28 11:48:19 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
	static void	get_path(t_data *data, char **env)

		* This function extracts the PATH environment variable from the given
			environment array.
		* It iterates through the environment array to find the PATH variable.
		* Once found, it allocates memory for a copy of the PATH string and
			splits it into individual paths using the px_split function.
		* The resulting paths are stored in the data->path array.
*/
static void	get_path(t_data *data, char **env)
{
	int		i;
	int		j;
	char	*path_line;

	i = 0;
	j = 5;
	while (env[i] && px_strncmp(env[i], "PATH=", j))
		i++;
	if (!env[i])
		exit(2);
	path_line = px_calloc(px_strlen(&env[i][j]) + 1, sizeof(char));
	px_strlcpy(path_line, &env[i][j], px_strlen(&env[i][j]) + 1);
	data->path = px_split(path_line, ':');
}

/*
	void	process(char *command, t_data *data)

	* This function executes a given command by searching for its executable
		file in the directories listed in the PATH environment variable.
	* It first calls the get_path function to obtain the list of
		directories in the PATH.
	* Then, it splits the command string into individual command and argument
		tokens using the px_split function.
	* Next, it iterates through each directory in the PATH array and constructs
			the full path to the command executable by appending the command
			name to each directory path.
	* For each constructed path, it checks if the file exists (F_OK) and
			is executable (X_OK) using the access function.
	* If a valid executable file is found, it executes
			the command using the execve function.
	* If no executable file is found in any directory, it calls the path_errors
		function to handle the error case.
*/
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
			if (!access(pth_cmd, X_OK))
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
