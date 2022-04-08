/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 05:56:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/26 05:56:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* fork & open */
#include <sys/types.h>

/* open */
#include <sys/stat.h>
#include <fcntl.h>

/* fork & pipe */
#include <unistd.h>

/* exit  */
#include <stdlib.h>

/* own: libft */
#include "../libft/libft.h"

typedef struct	s_pipex
{
	int	pipe[2];
	int	fd_in;
	int	fd_out;
	char	*env_path;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_split;
	char	**cmd2_split;
	pid_t	process_id1;
	pid_t	process_id2;
}				t_pipex;

#endif
