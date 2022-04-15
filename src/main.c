/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:11:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fdin;
	int		fdout;
	char	*env_path;

	if (argc != 5)
	{
		ft_putstr_fd("$RES_REAL: ambiguous redirect\n", 2);
		return (1);
	}
	fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fdout == -1)
		exit(1);
	fdin = read_file(argv[1]);
	env_path = get_env_path(envp);
	if (!env_path)
		exit(1);
	if (dup2(fdin, 0) == -1)
		exit(1);
	if (dup2(fdout, 1) == -1)
		exit(1);
	pipex(argv[2], envp, env_path);
	run_cmd(argv[3], envp, env_path);
	return (0);
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
			exit(1);
		}
		tmp_cmd_path = px_strjoin(dir, cmd);
		if (!tmp_cmd_path)
		{
			free(tmp_cmd_path);
			free(dir);
			exit(1);
		}
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
			return (tmp_cmd_path);
		free(tmp_cmd_path);
		path = path + ft_strchr_pos(path, ':') + 1;
	}
	return (cmd);
}

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
				exit(1);
			return (env_path);
		}
		i++;
	}
	exit(1);
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

void	error_msg(char	*cmd, char *s)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*s;

	i = 0;
	if ((!(src)) || (len == 0))
		return (NULL);
	s = malloc(sizeof(char) * len + 1);
	while ((src[i]) && (i < (len - 1)))
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < n)
	{
		if ((!s1_uc[i]) && (s1_uc[i] == s2_uc[i]))
			return (0);
		if (s1_uc[i] != s2_uc[i])
			return (s1_uc[i] - s2_uc[i]);
		i++;
	}
	return (0);
}

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

int	read_file(char	*file)
{
	if (access(file, F_OK) == 0)
		return (open(file, O_RDONLY, 0777));
	error_msg(file, ": no such file or directory");
	return (-1);
}
