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

#include "pipex.h"

int		msg_return(char *cmd, int ret_status);
void	msg_exit(char *cmd, int exit_status);
int		check_input_validity(int argc, char **argv, t_pipex *env);
int		open_file(char **argv, t_pipex *env);

int	main(int argc, char **argv)
{
	// (void)argc;
	// (void)argv;
	// (void)envp;
	t_pipex	*env;

	env = ft_calloc_new(1, sizeof(env));
	//if (check_input_validity(argc, argv, env))
	//	return(msg_return("Usage: ./pipex [input][cmd1][cmd2][output]", 1));
	if (!env)
		msg_exit("Could not allocate memory for the env", 1);
	check_input_validity(argc, argv, env);
	(void)env;
	
	msg_return("Reached the end..", 1);
	//msg_exit("exit message", 1);
	return (0);
}


int		open_file(char **argv, t_pipex *env)
{
	env->fd_in = open(argv[1], O_RDONLY);
	if (env->fd_in == -1)
		return(msg_return("Could not open input file", 1));
	env->fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	return(0);
}

int		check_input_validity(int argc, char **argv, t_pipex *env)
{
	if (argc != 5)
		return(msg_return("Usage: ./pipex [input][cmd1][cmd2][output]", 1));	
	open_file(argv, env);
	return (0);	
}

int		msg_return(char *cmd, int ret_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return(ret_status);
}

void	msg_exit(char *cmd, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}