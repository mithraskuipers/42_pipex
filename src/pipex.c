/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/01 21:39:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
dup2(pipefd[1], STDOUT_FILENO);
Als een process de stdoutput gebruikt om te printen,
gaat het niet naar stdout, maar naar de write deel van de pipe

dup2(pipefd[0], STDIN_FILENO);
Als een proces uit stdin leest, doet het dat niet,
maar leest het uit read gedeelte van pipe
*/


#include "pipex.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


#define PIPE_WRITE 1
#define PIPE_READ 0

int		ft_error(char *s, int errno);
//int	pipex_error(char *s);
int		pipex_open_mode(char *filename, int mode);
void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp);
int		child_process(int fd_input, char *cmd1);

char	**ft_split(char const *s, char c);




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

void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp)
{
	int	fd_pipe[2];
	int processes;
	
	pipe(fd_pipe);
	processes = fork();
	
	if (processes < 0)
		return (perror("Fork: "));
	
	// child
	// is simply used to REDIRECT OUTPUT
	// dup2(X,Y), whatever X had opened, is now also opened by Y
	if (processes == 0)
	{
		dup2(fd_input, STDIN_FILENO); // STDIN haalt nu data uit input file
		close(fd_pipe[0]); // close read end of pipe, because not used
		dup2(fd_pipe[1], STDOUT_FILENO); // STDOUT gebeurt nu in writing end of pipe
	}
	// parent
	if (processes > 0)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
	}
		
}

/*
int	child_process(int fd_input, char *cmd1)
{
	//
	return (0);
}
*/

int	main(int argc, char **argv, char **envp)
{
	int fd_input;
	int fd_output;

	if (argc != 5)
		pipex_error("Invalid input. Please input 4 arguments.\n");
	fd_input = pipex_open_mode(argv[1], MODE_INPUT);
	fd_output = pipex_open_mode(argv[4], MODE_OUTPUT);


	pipex(fd_input, fd_output, cmd1, cmd2, envp);
	//close(fd_input);
	//close(fd_output);
	return (0);
}