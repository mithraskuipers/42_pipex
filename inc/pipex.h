/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 11:27:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#define MODE_INPUT 0
#define MODE_OUTPUT 1
#define PIPE_WRITE 1
#define PIPE_READ 0

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct	s_pipex
{
	char *cmd1;
	char *cmd2;
	char **cmd1args;
	char **cmd2args;
	int fd_in;
	int fd_out;
	int fd_pipe[2];
	int pid1;
	int pid2;
	char *tmp_path;
	char	**paths;
	char	**cmds;
	char	*path;
	
}				t_pipex;

int	pipex(char **argv, char **envp, t_pipex *env);
void	*ft_calloc(size_t count, size_t size);
void	exit_all(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int	ft_strchr(const char *s, int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
