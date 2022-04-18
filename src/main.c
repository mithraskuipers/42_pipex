/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/18 17:47:54 by mikuiper      ########   odam.nl         */
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

TODO
if infile niet bestaat dan dup2 niet protecten
if infile wel bestaat dan dup2 wel protecten