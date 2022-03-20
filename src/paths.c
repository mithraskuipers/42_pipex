/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 20:53:45 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 20:53:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_cmd_path(char *cmd, char *path)
{	
	char	*dir;
	char	*tmp_cmd_path;
	
	while (path && ft_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr(path, ':') + 1); // protect
		tmp_cmd_path = px_strjoin(dir, cmd); // protect
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
			return (tmp_cmd_path);
		free(tmp_cmd_path);
		path = path + ft_strchr(path, ':') + 1;
	}
	return (cmd);
}

int		read_file(char	*file)
{
	if (access(file, F_OK) == 0)
		return (open(file, O_RDONLY));
	error_msg(file);
	return (-1);
}

char	*get_path(char **envp)
{
	int		i;
	char	*base_path;
	
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], ft_strlen("PATH")))
		{
			base_path = ft_strndup(&envp[i][ft_strchr(envp[i], '=') + 1], \
			ft_strlen(&envp[i][ft_strchr(envp[i], '=') + 1]));
			if (!base_path)
				exit (1);
			return (base_path);
		}
		i++;
	}
	exit (1);
}

char	*px_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '/';
	i++;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

