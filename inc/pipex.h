/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/05 11:56:30 by mikuiper      ########   odam.nl         */
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

int		ft_error(char *s, int errno);
//int	pipex_error(char *s);
int		pipex_open_mode(char *filename, int mode);
//void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp);
int		pipex(char **argv, char **envp, int fd_in, int fd_out);
int		child_process(int fd_input, char *cmd1);
char	**ft_split(char const *s, char c);

int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int	ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);

#endif