/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:31:10 by ogoman            #+#    #+#             */
/*   Updated: 2024/03/12 08:36:32 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
/* perror() */

# include <unistd.h>
/* STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO,
	access(): F_OK, X_OK, fork(), execve(), pipe(), dup2()
*/

# include <stdlib.h>
/* malloc(), calloc(), free() */

# include <fcntl.h>
/* O_RDONLY (read only), O_RDWR (read and write), O_CREAT(create),
O_TRUNC (will overwrite if the file already exists), open(), close()
*/

# include <sys/types.h>
/* pid_t, size_t */

typedef struct s_data
{
	pid_t	pid1;
	pid_t	pid2;
	char	**av;
	char	**env;
	char	**path;
	char	**cmd_opt;
	int		fd[2];
	int		file_in;
	int		file_out;
	int		status;
}	t_data;

int		px_strcmp(const char *s1, const char *s2);
int		px_strncmp(const char *s1, const char *s2, size_t n);
void	processes_making(t_data *data);
void	process(char *cmd, t_data *data);
void	main_errors(int error);
void	path_errors(int error);
void	child_pid1(t_data *data);
void	child_pid2(t_data *data);
void	close_fd(t_data *data);
void	px_bzero(void *s, size_t n);
void	*px_calloc(size_t count, size_t size);
char	*px_strjoin(char const *s1, char const *s2);
char	*px_strdup(const char *s);
char	*px_substr(char const *s, unsigned int start, size_t len);
void	*px_memset(void *ptr, int value, size_t num);
char	**px_split(char const *str, char c);
size_t	px_strlen(const char *s);
size_t	px_strlcpy(char *dst, const char *src, size_t n);

#endif

/*
	pid_t	pid1/pid2; process identifier after calling the fork()
	char	**av; This is a pointer to a pointer to character
	char	**env; environment variables passed to the program
	char	**path; used to store paths to directories
	char	**cmd_opt; used to store command options passed to the program.
	int		fd[2]; create a pipe between two processes,reading and writing
	int		file_in; file descriptor for the input file (read)
	int		file_out; file descriptor for the output file (write)
	int		status; status code of the process
*/
