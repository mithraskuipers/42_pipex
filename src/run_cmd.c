/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:18:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(char *cmd, char **envp, char *env_path)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		dp_clean_void(args);
		exit(1);
	}
	cmd_path = get_cmd_path(args[0], env_path);
	if (!cmd_path)
	{
		free(cmd_path);
		dp_clean_void(args);
		exit(1);
	}
	if (cmd_path == args[0])
	{
		dp_clean_void(args);
		error_msg(cmd, ": command not found");
		exit(127);
	}
	if (execve(cmd_path, args, envp) == -1)
		exit(1);
}
