/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:31:10 by ogoman            #+#    #+#             */
/*   Updated: 2024/02/27 10:45:22 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
// perror()

# include <unistd.h>
// STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, access(): F_OK, X_OK, fork(), execve(), pipe(), dup2()

# include <stdlib.h>
// malloc(), calloc(), free()

# include <fcntl.h>
// O_RDONLY (read only), O_RDWR (read and write), O_CREAT(create), O_TRUNC (will overwrite if the file already exists)
// open(), close()

# include <sys/types.h>
// pid_t, size_t

// # include "libft/libft.h"

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
void	main_errors(int error);
void	path_errors(int error);
void	px_bzero(void *s, size_t n);
void	*px_calloc(size_t count, size_t size);
char	*px_strjoin(char const *s1, char const *s2);
char	**px_split(char const *s, char c);
size_t	px_strlen(const	char *str);
size_t	px_strlcpy(char *dst, const char *src, size_t n);
int		px_strncmp(const char *s1, const char *s2, size_t n);

#endif