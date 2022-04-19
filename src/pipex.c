/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:20:33 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 07:34:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *cmd, t_env *env)
{
	pid_t	process_id;

	if (pipe(env->fd_pipes) == -1)
		exit(EXIT_FAILURE);
	process_id = fork();
	if (process_id == -1)
		exit(EXIT_FAILURE);
	else if (process_id == 0)
	{
		if (close(env->fd_pipes[0]) == -1)
			exit(EXIT_FAILURE);
		if (dup2(env->fd_pipes[1], 1) == -1)
			exit(EXIT_FAILURE);
		run_cmd(cmd, env);
	}
	else
	{
		if (close(env->fd_pipes[1]) == -1)
			exit(EXIT_FAILURE);
		if (dup2(env->fd_pipes[0], 0) == -1)
			exit(EXIT_FAILURE);
		waitpid(process_id, NULL, 0);
	}
}
