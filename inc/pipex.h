/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 21:10:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

int		openfile(char *filename, int mode);
void	pipex(char *cmd, char **envp, char *base_path);
void	run_cmd(char *cmd, char **envp, char *base_path);
char	**ft_split(char const *s, char c);
char	*px_strjoin(char *s1, char *s2);
char	*ft_strndup(char *src, int len);
char	*find_cmd_path(char *cmd, char *path);
int		ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	dp_clean(char **dp);
void	ft_putstr_fd(char *s, int fd);
void	error_msg(char	*cmd);
int		read_file(char	*file);
char	*get_path(char **envp);
void	ft_putnbr_fd(int n, int fd);

#endif
