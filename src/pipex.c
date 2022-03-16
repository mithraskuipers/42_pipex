/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:49:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// als het gaat om een pointer is 0 == 0x0 == NULL

#include "pipex.h"

int	pipex(char **argv, char **envp, t_pipex *env)
{
	env->cmdset[0].cmd = find_cmd_path(argv[2], envp, env);
	env->cmdset[1].cmd = find_cmd_path(argv[3], envp, env);
	env->cmdset[0].cmdargs = ft_split(argv[2], ' ');
	env->cmdset[1].cmdargs = ft_split(argv[3], ' ');
	pipe(env->fd_pipe);
	env->pid1 = fork();
	if (env->pid1 < 0)
		free_all(env, "Forking failed.");
	else if (env->pid1 == 0)
		child(env->fd_in, env->fd_pipe[1], env->cmdset[0].cmd, env->cmdset[0].cmdargs, envp);
	else if (env->pid1 > 0)
	{
		wait(NULL);
		close(env->fd_pipe[1]);
		env->pid2 = fork();
		if (env->pid2 < 0)
			free_all(env, "Forking failed.");
		else if (env->pid2 == 0)
			child(env->fd_pipe[0], env->fd_out, env->cmdset[1].cmd, env->cmdset[1].cmdargs, envp);
		else if (env->pid2 > 0)
			wait(NULL);
		close_fd(*env);
	}
	return (0);
}
