/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 22:34:40 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/26 22:34:40 by mikuiper      ########   odam.nl         */
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

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;
	char	**cmd1;

	env = ft_calloc_new(1, sizeof(t_pipex));
	if (!env)
		msg_exit("Failed to allocate memory for env.", 1);
	if (check_input_validity(argc, argv, env))
		return (msg_return ("Usage: ./pipex [input][cmd1][cmd2][output]", 1));
	env->env_path = get_env_path(envp);

	// specific cmd
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
	{
		dp_clean_char(cmd1);
		msg_exit("Error.\nCould not obtain command data.", 1);
	}
	env->cmd_path1 = get_cmd_path(cmd1[0], env->env_path);
	env_cmd_path2 = get_cmd_path(cmd2[0], env->env_path);
	printf("%s", env->cmd_path);

	//msg_return ("Reached the end..", 1);
	//msg_exit("exit message", 1);
	return (0);
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
	close(env->pipe[0]);
	close(env->pipe[1]);
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
		return (msg_return ("Usage: ./pipex [input] [cmd1] [cmd2] [output]", 1));
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

