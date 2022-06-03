/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_paths.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:12:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 09:04:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path(char **envp)
{
	int		i;
	char	*env_path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], ft_strlen("PATH")))
		{
			env_path = ft_strndup(&envp[i][ft_strchr_pos(envp[i], '=') + 1], \
			ft_strlen(&envp[i][ft_strchr_pos(envp[i], '=') + 1]));
			if (!env_path)
				exit(EXIT_FAILURE);
			return (env_path);
		}
		i++;
	}
	exit(EXIT_FAILURE);
}

char	*get_cmd_path(char *cmd, char *path)
{	
	char	*dir;
	char	*tmp_cmd_path;

	while (path && ft_strchr_pos(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr_pos(path, ':') + 1);
		if (!dir)
		{
			free(dir);
			exit(EXIT_FAILURE);
		}
		tmp_cmd_path = px_strjoin(dir, cmd);
		if (!tmp_cmd_path)
		{
			free(tmp_cmd_path);
			free(dir);
			exit(EXIT_FAILURE);
		}
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
			return (tmp_cmd_path);
		free(tmp_cmd_path);
		path = path + ft_strchr_pos(path, ':') + 1;
	}
	return (cmd);
}
