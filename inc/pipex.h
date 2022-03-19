/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:11:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 16:32:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>


typedef struct s_cmd
{
	char	*cmd;
	char	**cmdargs;
}				t_cmd;

typedef struct s_pipex
{
	t_cmd	cmdset[2];
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	char	*tmp_path;
	char	**paths;
	char	**cmds;
	char	*path;
}				t_pipex;

#endif
