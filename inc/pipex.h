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

/* fork */
#include <sys/types.h>

/* fork & pipe */
#include <unistd.h>

/* exit  */
#include <stdlib.h>

/* own: libft */
#include "../libft/libft.h"

typedef struct	s_pipex
{
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	pid_t	X;
	pid_t	Y;
}				t_pipex;

#endif