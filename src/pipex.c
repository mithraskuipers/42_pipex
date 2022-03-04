/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/04 14:36:49 by mikuiper      ########   odam.nl         */
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

/*
void	execute(char *path, char *args, char **envp)
{
	
}

int		valid_cmds(char *cmd1, char *cmd2, char **envp)
{
	char **paths;

	paths = ft_split(en)

}
*/

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
	//return (NULL);
}

//make re && ./pipex infile ls wc outfile

/*
void	free_me(char *s)
{
	if (s)
	{
		free (s);
		//s = NULL;
	}
}
*/

//void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp)
char	*check_cmd_path(char *cmd, char **envp)
{
	char *cmd_path;
	cmd_path = find_cmd_path(cmd, envp);
	if (!cmd_path)
		exit(1);
	return (cmd_path);
}

int	pipex(char **argv, char **envp)
{
	char *cmd1;
	char *cmd2;

	//cmd1 = check_cmd_path(argv[2], envp);
	cmd1 = "/bin/ls";
	cmd2 = check_cmd_path(argv[3], envp);
	printf("%s\n", cmd1);
	//printf("%s\n", cmd2);
	//execve(cmd1, argv[2], envp);
	//printf("%s", argv[2]);
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

int	main(int argc, char **argv, char **envp)
{
	//printf("%d", access("/bin/ls", F_OK)); // 0 is goed, -1 is fout
	if (argc != 5)
		return (0);
	pipex(argv, envp);


	// voor iedere path, strjoin de cmd
	// probeer dan access
	// als access, execve

	
	//cmd_path = ft_strjoin()
	//printf("%s", cmd);
	//printf("%s", ft_split(argv[2], ' '));

	/*
	char *fullpath
	ft_split(cmd)[0]
	while (split_path[i])
	{
		fullpath = strjoin(split_path[i], ft_split(cmd[0], ' ')
		if (access(fullpath))
			return *fullpath
		else
			free(fullpath)
			fullpath = NULL
	}
	*/

	/*
	int fd_input;
	int fd_output;

	if (argc != 5)
		perror("Invalid input. Please input 4 arguments.\n");
	fd_input = pipex_open_mode(argv[1], MODE_INPUT);
	fd_output = pipex_open_mode(argv[4], MODE_OUTPUT);
	pipex(fd_input, fd_output, cmd1, cmd2, envp);
	//close(fd_input);
	//close(fd_output);
	*/
	return (0);
}

