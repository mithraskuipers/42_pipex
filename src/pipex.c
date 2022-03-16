/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 11:25:47 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// als het gaat om een pointer is 0 == 0x0 == NULL

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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_uc;

	i = 0;
	b_uc = (unsigned char *)b;
	while (i < len)
	{
		b_uc[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

char *get_paths(char *s, char **envp, t_pipex *env)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(s, envp[i], ft_strlen(s)))
		{
			env->path = ft_strdup(&envp[i][ft_strchr(envp[i], '=') + 1]);
			break;
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

char *find_cmd_path(char *cmd, char **envp, t_pipex *env)
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
	int nbytes;
	char c;

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

int	pipex(char **argv, char **envp, t_pipex *env)
{
	env->cmd1 = find_cmd_path(argv[2], envp, env);
	env->cmd2 = find_cmd_path(argv[3], envp, env);
	env->cmd1args = ft_split(argv[2], ' ');
	env->cmd2args = ft_split(argv[3], ' ');
	pipe(env->fd_pipe);
	env->pid1 = fork();
	if (env->pid1 < 0)
		free_all(env, "Forking failed.");
	else if (env->pid1 == 0)
		child(env->fd_in, env->fd_pipe[1], env->cmd1, env->cmd1args, envp);
	else if (env->pid1 > 0)
	{
		wait(NULL);
		close(env->fd_pipe[1]);
		env->pid2 = fork();
		if (env->pid2 < 0)
			free_all(env, "Forking failed.");
		else if (env->pid2 == 0)
			child(env->fd_pipe[0], env->fd_out, env->cmd2, env->cmd2args, envp);
		else if (env->pid2 > 0)
			wait(NULL);
		close_fd(*env);
	}
	return (0);
}
