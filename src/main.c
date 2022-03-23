/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 09:59:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/23 17:45:54 by mikuiper      ########   odam.nl         */
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
		ft_putstr_fd("invalid number of arguments.\n", 2);
		return (1);
	}
	fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fdout == -1)
		exit(1);
	fdin = read_file(argv[1]);
	if (fdin == -1)
		exit(file_error(argv[1], EXIT_FAILURE));
	env_path = get_env_path(envp);
	if (!env_path)
		exit(1);
	if (dup2(fdin, 0) == -1)
		exit(1);
	if (dup2(fdout, 1) == -1)
		exit(1);
	pipex(argv, envp, env_path, 0);
	return (0);
}
