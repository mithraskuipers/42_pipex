/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 11:16:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/13 11:16:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	msg_exit(char *cmd, int exit_status);
int		check_input_validity(int argc, char **argv, t_pipex *env);
void	open_file(char **argv, t_pipex *env);
void	get_paths(t_pipex *env, char **argv);
char	*get_env_path(t_pipex *env);
char	*get_cmd_path(char *cmd, char *path);
char	*px_strjoin(char *s1, char *s2);
int		pipe_handler(t_pipex *env);
int		pipe_stuff(t_pipex *env);
void	child(t_pipex *env, char *cmd, int *fd);
void	parent(t_pipex *env, char *cmd, int	*fd);
int		run_execve(t_pipex *env, char *cmd, char **split);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;

	env = ft_calloc_new(1, sizeof(t_pipex));
	if (!env)
		msg_exit("Failed to allocate memory for env.", EXIT_FAILURE);
	(void)envp;
	env->envp = envp;
	if (check_input_validity(argc, argv, env))
		msg_exit ("Usage: ./pipex [input][cmd1][cmd2][output]", 1);
	get_paths(env, argv);
	pipe_handler(env);



	return (0);
}

void	msg_exit(char *cmd, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

int		check_input_validity(int argc, char **argv, t_pipex *env)
{
	if (argc != 5)
		msg_exit ("Usage: ./pipex [input][cmd1][cmd2][output]", 1);
	open_file(argv, env);
	return (0);
}

void	open_file(char **argv, t_pipex *env)
{
	env->fd_in = open(argv[1], O_RDONLY);
	if (env->fd_in == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	env->fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (env->fd_out == -1)
		msg_exit("Could not open or create output file.", 1);
}

void get_paths(t_pipex *env, char **argv)
{
	env->env_path = get_env_path(env);
	env->cmd1_split = ft_split(argv[2], ' ');
	if (!env->cmd1_split)
		msg_exit("Error.\nCould not obtain command data.", 1);
	env->cmd2_split = ft_split(argv[3], ' ');
	if (!env->cmd1_split)
		msg_exit("Error.\nCould not obtain command data.", 1);
	env->cmd1_path = get_cmd_path(env->cmd1_split[0], env->env_path);
	if (!env->cmd1_path)
		msg_exit("Error.\nCould not split command data.", 1);
	/*
	if (env->cmd1_path == env->cmd1_split[0])
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(env->cmd1_split[0], 2);
		ft_putstr_fd("\n", 2);
	}
	*/
	env->cmd2_path = get_cmd_path(env->cmd2_split[0], env->env_path);
	if (!env->cmd2_path)
		msg_exit("Error.\nCould not split command data.", 1);
}

char	*get_env_path(t_pipex *env)
{
	int		i;
	char	*env_path;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp("PATH", env->envp[i], ft_strlen("PATH")))
		{
			env_path = ft_strndup(&env->envp[i][ft_strchr_pos(env->envp[i], '=') + 1], \
			ft_strlen(&env->envp[i][ft_strchr_pos(env->envp[i], '=')]));
			if (!env_path)
				msg_exit("Error.\nFailed to obtain environment data.", 1);
			return (env_path);
		}
		i++;
	}
	msg_exit("Error.\nFailed to obtain environment data.", 1);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char *path)
{	
	char	*dir;
	char	*tmp_cmd_path;

	while ((path) && (ft_strchr_pos(path, ':') != -1))
	{
		dir = ft_strndup(path, ft_strchr_pos(path, ':') + 1);
		if (!dir)
		{
			free(dir);
			msg_exit("Error.\nCould not obtain command path.", 1);
		}
		tmp_cmd_path = px_strjoin(dir, cmd);
		if (!tmp_cmd_path)
		{
			free(tmp_cmd_path);
			free(dir);
			msg_exit("Error.\nCould not obtain command path.", 1);
		}
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
			return (tmp_cmd_path);
		free(tmp_cmd_path);
		path = path + ft_strchr_pos(path, ':') + 1;
	}
	return (cmd);
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

int		pipe_handler(t_pipex *env)
{
	pid_t	forky;
	int		stat;
	int 	ret;
	
	forky = fork();
	if (forky == -1)
		exit(1); // fork error
	else if(forky == 0)
	{
		pipe_stuff(env);
		exit (5); // change to command output return
	}
	else
	{
		waitpid(-1, &stat, 0);
	}
	ret = WEXITSTATUS(stat);
	return (ret);
}

int		pipe_stuff(t_pipex *env)
{
	pid_t	forky;
	int		fd[2];
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	forky = fork();
	if (forky < 0)
	{
		exit(EXIT_FAILURE);
	}
	if (forky == 0)
	{
		child(env, env->cmd1_path, fd);
	}
	else
	{
		parent(env, env->cmd2_path, fd);
	}
	return (1);
}

void	child(t_pipex *env, char *cmd, int *fd)
{
	close (fd[0]);
	close(STDIN);
	dup2(env->fd_in, STDIN); // PROTECT ME
	if (dup2(fd[1], STDOUT) == -1)
		msg_exit("dup2() failed.", EXIT_FAILURE);
	close(fd[1]);
	env->ret = run_execve(env, cmd, env->cmd1_split);
	close(STDIN);
	close(STDOUT);

	// reset me pls
	exit(env->ret);
}

void	parent(t_pipex *env, char *cmd, int	*fd)
{
	close (fd[1]);
	close(STDOUT);
	if (dup2(fd[0], STDIN) == -1)
	{
		msg_exit("dup2() failed.", EXIT_FAILURE);
	}
	dup2(env->fd_out, STDOUT);
	close(fd[0]);
	env->ret = run_execve(env, cmd, env->cmd2_split);
	//execve(cmd, env->cmd2_split, env->envp);
	close(STDIN);
}

int		run_execve(t_pipex *env, char *cmd, char **split)
{
	pid_t forky;
	int stat;

	forky = fork();
	if (forky == -1)
		exit(1); 
	if (!forky)
	{
		if (execve(cmd, split, env->envp) < 0)
		{
			exit(127);
		}
	}
	else
		waitpid(forky, &stat, 0);
	return (WEXITSTATUS(stat));
}