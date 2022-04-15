/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:25:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* fork & open */
# include <sys/types.h>

/* fork & pipe */
# include <unistd.h>

/* wait */
# include <sys/wait.h>

/* open */
# include <sys/stat.h>
# include <fcntl.h>

/* exit  */
# include <stdlib.h>

/* own: libft */
# include "../libft/libft.h"

/* printf */
# include <stdio.h>

/* own: libft */
# include "../libft/libft.h"

int		read_file(char	*file);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(char *src, int len);
char	*get_cmd_path(char *cmd, char *path);
char	*get_env_path(char **envp);
char	*px_strjoin(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	error_msg(char	*cmd, char *s);;
void	pipex(char *cmd, char **envp, char *env_path);
void	run_cmd(char *cmd, char **envp, char *env_path);

#endif
