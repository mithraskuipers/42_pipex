/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 09:59:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 20:54:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
~/repos/pipex/PIPEXaminator
bash all_tests.sh

~/repos/pipex/pipex_tester_42
bash pipex_tester.sh m
*/

int		main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;
	char *base_path;

	if (argc != 5)
		ft_putstr_fd("Invalid number of arguments.\n", 2);
	else
	{
		fdin = read_file(argv[1]);
		fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fdin == -1)
			exit(1);
		dup2(fdin, 0);
		dup2(fdout, 1);
		base_path = get_path(envp);
		pipex(argv[2], envp, base_path);
		run_cmd(argv[3], envp, base_path);
	}
	return (1);
}
