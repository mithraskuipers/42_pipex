/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/28 14:01:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		ft_error(char *s, int errno);
int		ft_strlen(char *s);
//int	pipex_error(char *s);
int		pipex_open_mode(char *filename, int mode);
void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2);
int	child_process(int fd_input, char *cmd1);

int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
int	pipex_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	// free?
	return (1);
}
*/

int	pipex_open_mode(char *filename, int mode)
{
	if (mode == MODE_INPUT)
	{
		open(filename, O_RDONLY);
	}
	else if (mode == MODE_OUTPUT)
	{
		open(filename, O_CREAT | O_RDWR | O_TRUNC);
	}
	else
		perror("Could not open file.");
	return (1);
}

void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2)
{
	int	end[2];
	int status;
	pid_t	child;

	pipe(end);
	processes = fork();
	if (processes < 0)
		return (perror("Fork: "));
	if (processes == 0)
	{
		dup2(fd_input, 0); // 
		
		//child_process(fd_input, cmd1);
	}
		
}

/*
int	child_process(int fd_input, char *cmd1)
{
	//
	return (0);
}
*/

int	main(int argc, char **argv)
{
	int fd_input;
	int fd_output;

	if (argc != 5)
		pipex_error("Invalid input. Please input 4 arguments.\n");
	fd_input = pipex_open_mode(argv[1], MODE_INPUT);
	fd_output = pipex_open_mode(argv[4], MODE_OUTPUT);

	char *cmd1;
	cmd1 = "ls";
	char *cmd2;
	cmd2 = "ls";
	pipex(fd_input, fd_output, cmd1, cmd2);
	//close(fd_input);
	//close(fd_output);
	return (0);
}