/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:45:18 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:36:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;

	if (argc != 5)
		perror("Invalid input. Please input 4 arguments.\n");
	env = ft_calloc(1, sizeof(t_pipex));
	env->fd_in = open("infile", O_RDONLY);
	if (!env->fd_in)
		exit_all("Failed reading the output file.");
	env->fd_out = open("outfile", O_RDWR | O_APPEND | O_CREAT, 0666);
	if (!env->fd_out)
		exit_all("Failed reading the output file.");
	pipex(argv, envp, env);
	//system("leaks pipex");
	return (0);
}
