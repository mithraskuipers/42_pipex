/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/18 19:20:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(char *cmd, t_env *env)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		dp_clean_void(args);
		exit(1);
	}
	env->cmd_path = get_cmd_path(args[0], env->env_path);
	if (!env->cmd_path)
	{
		free(env->cmd_path);
		dp_clean_void(args);
		exit(1);
	}
	if (env->cmd_path == args[0])
	{
		dp_clean_void(args);
		error_msg(cmd, ": command not found");
		exit(127);
	}
	if (execve(env->cmd_path, args, env->envp) == -1)
		exit(1);
}
