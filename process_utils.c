/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 07:20:08 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/23 13:14:11 by ogoman           ###   ########.fr       */
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
}





//ft_strncmp ///
//ft_calloc ///
//ft_strlen ////
//ft_strlcpy ///
//ft_split
//ft_strjoin


///// prodolzit razbirat split ft_alloc_all////////