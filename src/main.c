/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 09:59:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/22 15:27:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fdin;
	int		fdout;
	char	*base_path;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	fdin = read_file(argv[1]);
	fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fdin == -1)
		exit(1);
	base_path = get_path(envp);
	dup2(fdin, 0);
	dup2(fdout, 1);
	pipex(argv[2], envp, base_path);
	run_cmd(argv[3], envp, base_path);
	return (0);
}
