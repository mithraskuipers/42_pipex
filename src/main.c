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
#include "../libft/libft.h"

int		msg_return(char *cmd, int ret_status);
void	msg_exit(char *cmd, int exit_status);
int		check_input_validity(int argc, char **argv, t_pipex *env);
void	open_file(char **argv, t_pipex *env);
void	pipes_close(t_pipex	*env);
char	*get_env_path(char **envp);

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;

	env = ft_calloc_new(1, sizeof(t_pipex));
	if (!env)
		msg_exit("Failed to allocate memory for env", 1);
	if (check_input_validity(argc, argv, env))
		return(msg_return("Usage: ./pipex [input][cmd1][cmd2][output]", 1));
	env->env_path = get_env_path(envp);
	//printf("%s", env->env_path);

	//msg_return("Reached the end..", 1);
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
			env_path = ft_strndup(&envp[i][ft_strchr_new(envp[i], '=') + 1], \
			ft_strlen(&envp[i][ft_strchr_new(envp[i], '=')]));
			if (!env_path)
				exit(1);
			return (env_path);
		}
		i++;
	}
	exit(1);
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
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	env->fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (env->fd_out == -1)
		msg_exit("Could not open or create output file.", 1);
}

int		check_input_validity(int argc, char **argv, t_pipex *env)
{
	if (argc != 5)
		return(msg_return("Usage: ./pipex [input] [cmd1] [cmd2] [output]", 1));
	open_file(argv, env);
	return (0);	
}

// Messages

int		msg_return(char *cmd, int ret_status)
{
	//ft_putstr_fd(cmd, 2);
	//ft_putstr_fd("\n", 2);
	(void)cmd;
	return(ret_status);
}

void	msg_exit(char *cmd, int exit_status)
{
	//ft_putstr_fd(cmd, 2);
	//ft_putstr_fd("\n", 2);
	(void)cmd;
	exit(exit_status);
}