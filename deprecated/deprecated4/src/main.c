/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 19:10:08 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/08 19:10:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//< infile ls | wc > outfile
//make re && ./pipex infile ls wc outfile

#include "pipex.h"

int		msg_return (char *cmd, int ret_status);
void	msg_exit(char *cmd, int exit_status);
int		check_input_validity(int argc, char **argv, t_pipex *env);
void	open_file(char **argv, t_pipex *env);
void	pipes_close(t_pipex	*env);
char	*get_env_path(char **envp);
char	*get_cmd_path(char *cmd, char *path);
char	*px_strjoin(char *s1, char *s2);
void	dp_clean_char(char **dp);
int		ft_strchr_pos(const char *s, int c);
void	fork_and_run(t_pipex *env, char **envp);
void	get_paths(t_pipex *env, char **argv, char **envp);
void	run_prep_end(t_pipex *env);
void	run_cmd(t_pipex *env, char **envp, int cmd_n, int fd_dup);

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;

	env = ft_calloc_new(1, sizeof(t_pipex));
	if (!env)
		msg_exit("Failed to allocate memory for env.", 1);
	if (check_input_validity(argc, argv, env))
		return (msg_return ("Usage: ./pipex [input][cmd1][cmd2][output]", 1));
	get_paths(env, argv, envp);
	if (pipe(env->pipe_fd) == -1)
		exit(1);
	fork_and_run(env, envp);
	run_prep_end(env);
	execve(env->cmd2_path, env->cmd2_split, envp);
	close(env->fd_out);
	return (0);
}

void	fork_and_run(t_pipex *env, char **envp)
{
	env->process_id1 = fork();
	if (env->process_id1 == -1)
		exit(1);
	else if (env->process_id1 == 0)
	{
		if (close(env->pipe_fd[0]) == -1)
			msg_exit("Failed to close the reading end of the pipe.", 1);
		if (dup2(env->pipe_fd[1], 1) == -1)
			msg_exit("Failed to run dup2().", 1);
		execve(env->cmd1_path, env->cmd1_split, envp);
	}
	else
	{
		if (close(env->pipe_fd[1]) == -1)
			msg_exit("Failed to close the writing end of the pipe.", 1);
		if (dup2(env->pipe_fd[0], 0) == -1)
			msg_exit("Failed to run dup2().", 1);
		waitpid(env->process_id1, NULL, 0);
	}
}

void	fork_and_run2(t_pipex *env, char **envp)
{
	env->process_id2 = fork();
	if (env->process_id2 == -1)
		exit(1);
	else if (env->process_id2 == 0)
	{
		if (close(env->pipe_fd[0]) == -1)
			msg_exit("Failed to close the reading end of the pipe.", 1);
		if (dup2(env->pipe_fd[1], 1) == -1)
			msg_exit("Failed to run dup2().", 1);
		execve(env->cmd2_path, env->cmd2_split, envp);
	}
	else
	{
		if (close(env->pipe_fd[1]) == -1)
			msg_exit("Failed to close the writing end of the pipe.", 1);
		if (dup2(env->pipe_fd[0], 0) == -1)
			msg_exit("Failed to run dup2().", 1);
		waitpid(env->process_id2, NULL, 0);
	}
}

void	run_prep_end(t_pipex *env)
{
	if (dup2(env->fd_out, 1) == -1)
		exit(1);
}

void get_paths(t_pipex *env, char **argv, char **envp)
{
	env->env_path = get_env_path(envp);
	env->cmd1_split = ft_split(argv[2], ' ');
	if (!env->cmd1_split)
		msg_exit("Error.\nCould not obtain command data.", 1);
	env->cmd2_split = ft_split(argv[3], ' ');
	if (!env->cmd1_split)
		msg_exit("Error.\nCould not obtain command data.", 1);
	env->cmd1_path = get_cmd_path(env->cmd1_split[0], env->env_path);
	if (!env->cmd1_path)
		msg_exit("Error.\nCould not split command data.", 1);
	env->cmd2_path = get_cmd_path(env->cmd2_split[0], env->env_path);
	if (!env->cmd2_path)
		msg_exit("Error.\nCould not split command data.", 1);
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
			ft_strlen(&envp[i][ft_strchr_pos(envp[i], '=')]));
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

// NOT USED YET
void	pipes_close(t_pipex	*env)
{
	close(env->pipe_fd[0]);
	close(env->pipe_fd[1]);
}

// Input

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

int		check_input_validity(int argc, char **argv, t_pipex *env)
{
	if (argc != 5)
		return (msg_return ("Usage: ./pipex [input][cmd1][cmd2][output]", 1));
	open_file(argv, env);
	return (0);
}

// Messages

int		msg_return (char *cmd, int ret_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret_status);
}

void	msg_exit(char *cmd, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

void	run_cmd(t_pipex *env, char **envp, int cmd_n, int fd_dup)
{
	int	fd_close;

	fd_close = 0;
	if (fd_dup == 0)
		fd_close = 1;
	else if (fd_dup == 1)
		fd_close = 0;
	dup2(env->pipe_fd[fd_dup], fd_dup);
	//close(env->pipe_fd[fd_close]);
	dup2(env->fd_in, fd_close);
	if (cmd_n == 1)
		execve(env->cmd1_path, env->cmd1_split, envp);
	else if (cmd_n == 2)
		execve(env->cmd2_path, env->cmd2_split, envp);
}