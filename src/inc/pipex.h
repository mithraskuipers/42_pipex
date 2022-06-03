/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 09:41:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* INCLUDES SECTION  */
/* fork & open */
# include <sys/types.h>

/* fork & pipe */
# include <unistd.h>

/* wait */
# include <sys/wait.h>

/* open */
# include <fcntl.h>

/* exit  */
# include <stdlib.h>

/* own: libft */
# include "../libft/libft.h"

/* printf */
# include <stdio.h>

/* own: libft */
# include "../libft/libft.h"

typedef struct s_env
{
	int		fdin;
	int		fdout;
	int		fd_pipes[2];
	char	**envp;
	char	*cmd_path;
	char	*env_path;
}			t_env;

void	read_io(char *infile_name, char *outfile_name, t_env *env);
char	*get_cmd_path(char *cmd, char *path);
char	*get_env_path(char **envp);
char	*px_strjoin(char *s1, char *s2);
void	pipex(char *cmd, t_env *env);
void	run_cmd(char *cmd, t_env *env);
void	msg_cmd_error(char	*cmd, char *s);
void	msg_exit(char *s, int exit_code);

#endif
