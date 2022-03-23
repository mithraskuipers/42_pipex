/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/20 21:49:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/20 21:49:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_child(char *cmd, char **envp, char *env_path)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		dp_clean(args);
		exit(130 + 1);
	}
	cmd_path = get_cmd_path(args[0], env_path);
	if (!cmd_path)
	{
		free(cmd_path);
		dp_clean(args);
		exit(130 + 2);
	}
	if (cmd_path == args[0])
	{
		dp_clean(args);
		cmd_error(cmd);
		exit(130 + 3);
	}
	if (execve(cmd_path, args, envp) == -1)
		exit(130 + 4);
}

static void run_parent(char *cmd, char **envp, char *env_path)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		dp_clean(args);
		exit(1);
	}
	cmd_path = get_cmd_path(args[0], env_path);
	if (!cmd_path)
	{
		free(cmd_path);
		dp_clean(args);
		exit(1);
	}
	if (cmd_path == args[0])
	{
		dp_clean(args);
		cmd_error(cmd);
		exit(127);
	}
	if (execve(cmd_path, args, envp) == -1)
		exit(1);
}

void	pipex(char **argv, char **envp, char *env_path, int stat)
{
	pid_t	process_id;
	int		fd_pipes[2];

	if (pipe(fd_pipes) == -1)
		exit(1);
	process_id = fork();
	if (process_id == -1)
		exit(1);
	else if (process_id == 0)
	{
		if (close(fd_pipes[0]) == -1)
			exit(1);
		if (dup2(fd_pipes[1], 1) == -1)
			exit(1);
		run_child(argv[2], envp, env_path);
	}
	else
	{
		if (close(fd_pipes[1]) == -1)
			exit(1);
		if (dup2(fd_pipes[0], 0) == -1)
			exit(1);
		waitpid(process_id, NULL, 0);
		if (WEXITSTATUS(stat) > 130)
		{
			// print error
			write(2, "dikke", 5);
			exit (WEXITSTATUS(stat) - 130);
		}
		run_parent(argv[3], envp, env_path);
	}
	stat++;
}
