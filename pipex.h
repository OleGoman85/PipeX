/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:31:10 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/23 13:15:19 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
// STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

# include <stdlib.h>
# include <signal.h>

# include <fcntl.h>
// O_RDONLY (read only), O_RDWR (read and write), O_CREAT(create), O_TRUNC (will overwrite if the file already exists)
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_data
{
	pid_t	pid;
	char	**av;
	char	**env;
	char	**path;
	char	**cmd_opt;
	int		fd[2];
	int		file_in;
	int		file_out;
}	t_data;


void	processes_making(t_data *data);
void	process(char *cmd, t_data *data);
void 	main_errors(int error);
void	get_path(t_data *data, char **env);
int		px_strncmp(const char *s1, const char *s2, size_t n);
size_t	px_strlen(const char *str);
char	*px_calloc(size_t count, size_t size);
size_t	px_strlcpy(char *dest, const char *src, size_t size);

#endif