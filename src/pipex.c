/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/15 11:33:19 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// als het gaat om een pointer is 0 == 0x0 == NULL

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

void	free_all(t_pipex env, char *s)
{
	if (env.cmd1)
		free (env.cmd1);
	if (env.cmd2)
		free (env.cmd2);
	if (env.cmd1args)
		dp_clean(env.cmd1args);
	if (env.cmd2args)
		dp_clean(env.cmd2args);
	perror(s);
}

char *get_paths(char *s, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], ft_strlen(s)))
			return (ft_strdup(&envp[i][ft_strchr(envp[i], '=') + 1]));
		i++;
	}
	return (NULL);
}

char *find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp_path;
	char	**cmds;

	i = 0;
	path = get_paths("PATH", envp);
	if (!path)
		exit_all("Error. Failed to get PATH from env.");
	if (path && path[0] == '\0')
		exit_all("Error. PATH from env is empty.");
	paths = ft_split(path, ':');
	if (!paths)
		exit_all("Error. Failed to parse PATH from env.");
	cmds = ft_split(cmd, ' ');
	if (!cmds)
		exit_all("Error. Failed to parse user command input.");
	while (paths[i])
	{
		//tmp_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmds[0]);
		tmp_path = ft_strjoin(paths[i], cmds[0]);
		printf("joined: %s\n\n\n\n", tmp_path);
		if (!tmp_path)
			exit_all("Error. Failed to join PATH directory with command.");
		if (access(tmp_path, F_OK) == 0)
		{
			free (path);
			free (cmds);
			dp_clean(paths);
			return (tmp_path);
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

void	child(int a, int b, char *prog, char **prog_args, char **envp)
{
	close(0);
	dup2(a, 0);
	close(1);
	dup2(b, 1);
	execve(prog, prog_args, envp);
	exit(1);
}

void	close_fd(t_pipex env)
{
	int nbytes;
	char c;

	nbytes = read(env.fd_in, &c, 1);
	if (nbytes == -1)
		close (env.fd_in);
	nbytes = read(env.fd_out, &c, 1);
	if (nbytes == -1)
		close (env.fd_out);
	nbytes = read(env.fd_pipes[0], &c, 1);
	if (nbytes == -1)
		close (env.fd_pipes[0]);
	nbytes = read(env.fd_pipes[1], &c, 1);
	if (nbytes == -1)
		close (env.fd_pipes[1]);
}

int	pipex(char **argv, char **envp, t_pipex env)
{
	env.cmd1 = check_cmd_path(argv[2], envp);
	env.cmd2 = check_cmd_path(argv[3], envp);
	env.cmd1args = ft_split(argv[2], ' ');
	env.cmd2args = ft_split(argv[3], ' ');
	pipe(env.fd_pipes);
	env.pid1 = fork();
	if (env.pid1 < 0)
		free_all(env, "Forking failed.");
	else if (env.pid1 == 0)
		child(env.fd_in, env.fd_pipes[1], env.cmd1, env.cmd1args, envp);
	else if (env.pid1 > 0)
	{
		wait(NULL);
		close(env.fd_pipes[1]);
		env.pid2 = fork();
		if (env.pid2 < 0)
			free_all(env, "Forking failed.");
		else if (env.pid2 == 0)
			child(env.fd_pipes[0], env.fd_out, env.cmd2, env.cmd2args, envp);
		else if (env.pid2 > 0)
			wait(NULL);
		close_fd(env);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		perror("Invalid input. Please input 4 arguments.\n");

	t_pipex env;

	env.fd_in = open("infile", O_RDONLY);
	if (!env.fd_in)
		exit_all("Failed reading the output file.");
	env.fd_out = open("outfile", O_RDWR | O_APPEND |  O_CREAT, 0666);
	if (!env.fd_out)
		exit_all("Failed reading the output file.");
	pipex(argv, envp, env);
	system("leaks pipex");

	/*
	int fdnew;
	fdnew = open("infile", O_RDONLY);
	printf("fd of fdnew = %d\n", fdnew);
	close(fdnew);	
	char c;
	printf("fd of fdnew = %d\n", fdnew);
	int tmp;
	tmp = read(fdnew, &c, 1);
	printf("HOEVEEL GELEZEN? %d", tmp);
	*/
	return (0);
}