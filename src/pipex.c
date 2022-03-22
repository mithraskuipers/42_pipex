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

void	pipex(char *cmd, char **envp, char *base_path)
{
	pid_t	process_id;
	int		fd_pipes[2];

	pipe(fd_pipes);
	process_id = fork();
	if (process_id == 0)
	{
		close(fd_pipes[0]);
		dup2(fd_pipes[1], 1);
		run_cmd(cmd, envp, base_path);
	}
	else if (process_id > 0)
	{
		close(fd_pipes[1]);
		dup2(fd_pipes[0], 0);
		waitpid(process_id, NULL, 0);
	}
}

void	run_cmd(char *cmd, char **envp, char *base_path)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		dp_clean(args);
		exit(1);
	}
	cmd_path = find_cmd_path(args[0], base_path);
	if (!cmd_path)
	{
		free (cmd_path);
		dp_clean(args);
		exit(1);
	}
	if (cmd_path == args[0])
	{
		dp_clean(args);
		error_msg(cmd);
		exit(127);
	}
	execve(cmd_path, args, envp);
}
