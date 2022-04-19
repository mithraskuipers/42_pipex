/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 07:26:06 by mikuiper      ########   odam.nl         */
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
		exit(EXIT_FAILURE);
	}
	env->cmd_path = get_cmd_path(args[0], env->env_path);
	if (!env->cmd_path)
	{
		free(env->cmd_path);
		dp_clean_void(args);
		exit(EXIT_FAILURE);
	}
	if (env->cmd_path == args[0])
	{
		dp_clean_void(args);
		msg_cmd_error(cmd, ": command not found", 2);
		exit(127);
	}
	if (execve(env->cmd_path, args, env->envp) == -1)
		exit(EXIT_FAILURE);
}
