/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 12:59:58 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:34:35 by mikuiper      ########   odam.nl         */
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

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	size_t			len;
	unsigned char	*b_uc;
	unsigned char	c;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	i = 0;
	len = count * size;
	b_uc = (unsigned char *)ptr;
	c = 0;
	while (i < len)
	{
		b_uc[i] = c;
		i++;
	}
	return (ptr);
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
	find_cmd_path_cleaner(env);
	exit (1);
}

void	child(int a, int b, char *prog, char **prog_args, char **envp)
{
	close(0);
	dup2(a, 0);
	close(1);
	dup2(b, 1);
	execve(prog, prog_args, envp);
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
