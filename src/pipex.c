/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/25 16:08:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

int	ft_error(char *s, int errno);

typedef struct s_state
{
	
}				t_state;

static int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	pipex_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	// free?
	return (1);
}

int pipex_open_mode(char *filename, int mode)
{
	if (mode == MODE_INPUT)
	{
		//DO
	}
	else if (mode == MODE_OUTPUT)
	{
		//DO	
	}
	else
		pipex_error("");
}

int	main(int argc, char **argv)
{
	int fd_input;
	int fd_output;

	if (argc != 5)
		pipex_error("Invalid input. n arguments != 5\n");
	fd_input = pipex_open_mode(argv[1], MODE_INPUT);
	fd_output = pipex_open_mode(argv[4], MODE_OUTPUT);

	return (0);
}