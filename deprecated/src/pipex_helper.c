/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_helper.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 12:59:58 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/17 11:10:02 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_paths(char *s, char **envp, t_pipex *env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], ft_strlen(s)))
		{
			env->path = ft_strdup(&envp[i][ft_strchr(envp[i], '=') + 1]);
			break ;
		}
		i++;
	}
	if ((!env->path) || (env->path && env->path[0] == '\0'))
		exit_all("Error. Failed to get PATH from env.");
	env->paths = ft_split(env->path, ':');
	if (!env->paths)
		exit_all("Error. Failed to parse PATH from env.");
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp, t_pipex *env)
{
	int	i;

	i = 0;
	get_paths("PATH", envp, env);
	env->cmds = ft_split(cmd, ' ');
	if (!env->cmds)
		exit_env_clean("Error. Failed to parse user command input.", env);
	while (env->paths[i])
	{
		env->tmp_path = ft_strjoin(env->paths[i], env->cmds[0]);
		if (!env->tmp_path)
			exit_env_clean("Error. strjoin() failed.", env);
		else if (!access(env->tmp_path, F_OK))
		{
			find_cmd_path_cleaner(env);
			return (env->tmp_path);
		}
		free (env->tmp_path);
		ft_memset(env->tmp_path, 0, ft_strlen(env->tmp_path));
		i++;
	}
	return (cmd);
	//find_cmd_path_cleaner(env);
	//exit (1);
}

void	child(int fd1, int fd2, t_cmd cmdset, char **envp)
{
	close(0);
	dup2(fd1, 0);
	close(1);
	dup2(fd2, 1);
	//system("ls -la > result.txt")
	execve(cmdset.cmd, cmdset.cmdargs, envp);
	exit(1);
}

void	close_fd(t_pipex env)
{
	int		nbytes;
	char	c;

	nbytes = read(env.fd_in, &c, 1);
	if (nbytes == -1)
		close (env.fd_in);
	nbytes = read(env.fd_out, &c, 1);
	if (nbytes == -1)
		close (env.fd_out);
	nbytes = read(env.fd_pipe[0], &c, 1);
	if (nbytes == -1)
		close (env.fd_pipe[0]);
	nbytes = read(env.fd_pipe[1], &c, 1);
	if (nbytes == -1)
		close (env.fd_pipe[1]);
}
