/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:48:33 by mikuiper      ########   odam.nl         */
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

typedef struct	s_cmd
{
	char *cmd;
	char **cmdargs;
}				t_cmd;

typedef struct	s_pipex
{
	t_cmd cmdset[2];
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

int		pipex(char **argv, char **envp, t_pipex *env);
void	*ft_calloc(size_t count, size_t size);
void	exit_all(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	dp_clean(char **dp);
void	find_cmd_path_cleaner(t_pipex *env);
void	exit_env_clean(char *s, t_pipex *env);

void	free_all(t_pipex *env, char *s);
void	*ft_memset(void *b, int c, size_t len);
char	*get_paths(char *s, char **envp, t_pipex *env);
void	*ft_calloc(size_t count, size_t size);
char	*find_cmd_path(char *cmd, char **envp, t_pipex *env);
void	child(int fd1, int fd2, char *prog, char **prog_args, char **envp);
void	close_fd(t_pipex env);

#endif
