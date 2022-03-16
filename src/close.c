/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 13:31:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:32:46 by mikuiper      ########   odam.nl         */
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

void	find_cmd_path_cleaner(t_pipex *env)
{
	if (env->paths)
		dp_clean(env->paths);
	if (env->path)
		free (env->path);
	if (env->cmds)
		dp_clean(env->cmds);
	if (env->cmd1args)
		dp_clean(env->cmd1args);
	if (env->cmd2args)
		dp_clean(env->cmd2args);
}

void	exit_env_clean(char *s, t_pipex *env)
{
	perror(s);
	find_cmd_path_cleaner(env);
	exit (1);
}

void	free_all(t_pipex *env, char *s)
{
	if (env->cmd1)
		free (env->cmd1);
	if (env->cmd2)
		free (env->cmd2);
	if (env->cmd1args)
		dp_clean(env->cmd1args);
	if (env->cmd2args)
		dp_clean(env->cmd2args);
	perror(s);
}
