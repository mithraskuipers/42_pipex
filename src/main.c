/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:17:49 by mikuiper      ########   odam.nl         */
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

void	error_msg(char	*cmd, char *s)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
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
