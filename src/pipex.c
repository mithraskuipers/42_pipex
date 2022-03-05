/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/05 17:52:29 by mikuiper      ########   odam.nl         */
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

char *get_paths(char *s, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], ft_strlen(s)))
		{
			return (ft_strdup(&envp[i][ft_strchr(envp[i], '=') + 1]));
		}
		i++;
	}
	return (NULL);
}

typedef struct	s_pipex
{
	char *cmd1_program;
	char *cmd2_program;
	char **cmd1_args;
	char **cmd2_args;
}				t_pipex;

char *find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;
	char	**cmds;

	i = 0;
	path = get_paths("PATH", envp);
	paths = ft_split(path, ':');
	cmds = ft_split(cmd, ' ');
	while (paths[i])
	{
		tmp = ft_strjoin(ft_strjoin(paths[i], "/"), cmds[0]);
		if (access(tmp, F_OK) == 0)
		{
			free (path);
			free (paths);
			return (tmp);
		}
		i++;
	}
	free (path);
	free (paths);
	exit (1);
}

void	dp_clean(char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i])
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

void	free_all(t_pipex pipex_env)
{
	if (pipex_env.cmd1_program)
		free (pipex_env.cmd1_program);
	if (pipex_env.cmd2_program)
		free (pipex_env.cmd2_program);
	if (pipex_env.cmd1_args)
		dp_clean(pipex_env.cmd1_args);
	if (pipex_env.cmd2_args)
		dp_clean(pipex_env.cmd2_args);
}

//void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp)
char	*check_cmd_path(char *cmd, char **envp)
{
	char *cmd_path;
	cmd_path = find_cmd_path(cmd, envp);
	if (!cmd_path)
		exit(1);
	return (cmd_path);
}

int	pipex(char **argv, char **envp, int fd_in, int fd_out)
{
	t_pipex pipex_env;

	int pid1;
	int pid2;
	int fd_pipes[2];

	pipex_env.cmd1_program = check_cmd_path(argv[2], envp);
	pipex_env.cmd2_program= check_cmd_path(argv[3], envp);
	//printf("%s", argv[2]);
	pipex_env.cmd1_args = ft_split(argv[2], ' ');
	pipex_env.cmd2_args = ft_split(argv[3], ' ');
	pipe(fd_pipes);
	pid1 = fork(); // makes exact copy of the running process
	// int FD_CPY_STDIN = dup(0);
	// int FD_CPY_STDOUT = dup(1);

	if (pid1 < 0)
		perror("Forking failed.\n");
	// child process
	else if (pid1 == 0)
	{
		printf("Child is going to DIE\n");
		close(0);
		dup2(fd_in, 0);
		// close(fd_pipes[0]);
		close(1);
		dup2(fd_pipes[1], 1); // kan nu schrijven naar pipe
		execve(pipex_env.cmd1_program, pipex_env.cmd1_args, envp); // gaat nu schrijven naar pipe
		exit(1);
	}
	else if (pid1 > 0)
	{
		//waitpid(pid1, NULL, 0); // anders kan pid1==0 te laat gebeuren
		// waitpid(-1, 0, 0);
		wait(NULL);
		close(fd_pipes[1]);
		printf("Child is DEAD\n");

		pid2 = fork();
		if (pid2 < 0)
			perror("Forking failed.\n");
		else if (pid2 == 0)
		{
			close(0);
			dup2(fd_pipes[0], 0); // als die moet lezen, lees dan uit pipe (hier is door child in geschreven)
			close(1);
			dup2(fd_out, 1); // als die moet schrijven,schrijf dan naar fd_out
			// printf("!!!!\n");
			// close(fd_pipes[0]);
			execve(pipex_env.cmd2_program, pipex_env.cmd2_args, envp); // gaat nu schrijven naar pipe
			exit(1);
		}
		else if (pid2 > 0)
			wait(NULL);
		close(fd_pipes[0]);
		close(fd_in);
		close(fd_out);
		
			// waitpid(-1, 0, 0);
			//waitpid(pid2, NULL, 0);
		printf("Ha;p!");
	}
	//while (1);
	return (0);
}

// als het gaat om een pointer is 0 == 0x0 == NULL

int	main(int argc, char **argv, char **envp)
{
	//printf("%d", access("/bin/ls", F_OK)); // 0 is goed, -1 is fout
	if (argc != 5)
		perror("Invalid input. Please input 4 arguments.\n");

	int fd_in;
	int fd_out;

	fd_in = open("infile", O_RDONLY);
	// PROTECT
	fd_out = open("outfile", O_RDWR | O_APPEND |  O_CREAT, 0666);
	// PROTECT
	//write(fd_out, "Hallo", 5);
	pipex(argv, envp, fd_in, fd_out);

	//printf("%d", fd_in);
	//printf("%d", fd_out);
	return (0);
}



/*
int		d_pipe[2];
int		pid;

pipe(fd_pipe);
pid = fork();

if (pid < 0)
	return (perror("Fork: "));

// child
if (pid == 0)
{
	dup2(fd_input, STDIN_FILENO);
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	//execute(???);
}
// parent
if (pid > 0)
{
	dup2(fd_output, STDOUT_FILENO);
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
}
*/