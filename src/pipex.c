/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:20:33 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:20:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *cmd, char **envp, char *env_path)
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
		run_cmd(cmd, envp, env_path);
	}
	else
	{
		if (close(fd_pipes[1]) == -1)
			exit(1);
		if (dup2(fd_pipes[0], 0) == -1)
			exit(1);
		waitpid(process_id, NULL, 0);
	}
}
