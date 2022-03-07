/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/05 18:02:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_all(char *s)
{
	perror(s);
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

void	free_all(t_pipex pipex_env, char *s)
{
	if (pipex_env.cmd1_program)
		free (pipex_env.cmd1_program);
	if (pipex_env.cmd2_program)
		free (pipex_env.cmd2_program);
	if (pipex_env.cmd1_args)
		dp_clean(pipex_env.cmd1_args);
	if (pipex_env.cmd2_args)
		dp_clean(pipex_env.cmd2_args);
	perror(s);
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

char *find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;
	char	**cmds;

	i = 0;
	path = get_paths("PATH", envp);
	if (!path)
		exit_all("Error. Failed to get PATH from env.");
	if (path && path[0] == '\0')
		exit_all("Error. PATH is empty.");
	paths = ft_split(path, ':');
	cmds = ft_split(cmd, ' ');
	while (paths[i])
	{
		tmp = ft_strjoin(ft_strjoin(paths[i], "/"), cmds[0]);
		if (access(tmp, F_OK) == 0)
		{
			free (path);
			dp_clean(paths);
			return (tmp);
		}
		i++;
	}
	free (path);
	dp_clean(paths);
	exit (1);
}

char	*check_cmd_path(char *cmd, char **envp)
{
	char *cmd_path;
	cmd_path = find_cmd_path(cmd, envp);
	if (!cmd_path)
		exit(1);
	return (cmd_path);
}

int	pipex(char **argv, char **envp, t_pipex pipex_env)
{

	int pid1;
	int pid2;
	int fd_pipes[2];

	pipex_env.cmd1_program = check_cmd_path(argv[2], envp);
	pipex_env.cmd2_program= check_cmd_path(argv[3], envp);
	pipex_env.cmd1_args = ft_split(argv[2], ' ');
	pipex_env.cmd2_args = ft_split(argv[3], ' ');
	pipe(fd_pipes);
	pid1 = fork(); // makes exact copy of the running process
	if (pid1 < 0)
		free_all(pipex_env, "Forking failed.");
	else if (pid1 == 0)
	{
		close(0);
		dup2(pipex_env.fd_in, 0);
		close(1);
		dup2(fd_pipes[1], 1);
		execve(pipex_env.cmd1_program, pipex_env.cmd1_args, envp);
		exit(1);
	}
	else if (pid1 > 0)
	{
		wait(NULL);
		close(fd_pipes[1]);

		pid2 = fork();
		if (pid2 < 0)
			free_all(pipex_env, "Forking failed.");
		else if (pid2 == 0)
		{
			close(0);
			dup2(fd_pipes[0], 0);
			close(1);
			dup2(pipex_env.fd_out, 1);
			execve(pipex_env.cmd2_program, pipex_env.cmd2_args, envp);
			exit(1);
		}
		else if (pid2 > 0)
			wait(NULL);
		close(fd_pipes[0]);
		close(pipex_env.fd_in);
		close(pipex_env.fd_out);
	}
	return (0);
}



// als het gaat om een pointer is 0 == 0x0 == NULL

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		perror("Invalid input. Please input 4 arguments.\n");

	t_pipex pipex_env;

	pipex_env.fd_in = open("infile", O_RDONLY);
	if (!pipex_env.fd_in)
		exit_all("Failed reading the output file.");
	pipex_env.fd_out = open("outfile", O_RDWR | O_APPEND |  O_CREAT, 0666);
	if (!pipex_env.fd_out)
		exit_all("Failed reading the output file.");
	pipex(argv, envp, pipex_env);
	return (0);
}