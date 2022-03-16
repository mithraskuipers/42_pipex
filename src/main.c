/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:45:18 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/16 13:56:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*env;

	if (argc != 5)
		exit_all("Invalid input. Please input 4 arguments.");
	env = ft_calloc(1, sizeof(t_pipex));
	if (!env)
		exit_all("Failed allocating memory for struct.");
	env->fd_in = open("infile", O_RDONLY);
	if (!env->fd_in)
		exit_all("Failed reading the output file.");
	env->fd_out = open("outfile", O_RDWR | O_APPEND | O_CREAT, 0666);
	if (!env->fd_out)
		exit_all("Failed reading the output file.");
	pipex(argv, envp, env);
	system("leaks pipex");
	return (0);
}
