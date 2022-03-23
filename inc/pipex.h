/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/23 17:43:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

int		read_file(char	*file);
int		ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strndup(char *src, int len);
char	**ft_split(char const *s, char c);
char	*get_cmd_path(char *cmd, char *path);
char	*get_env_path(char **envp);
char	*px_strjoin(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	cmd_error(char	*cmd);
int		file_error(char *cmd, int ret);
void	dp_clean(char **dp);
void	pipex(char **argv, char **envp, char *env_path, int stat);

#endif
