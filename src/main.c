/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 07:40:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 08:08:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		exit(1);
	if (argc != 5)
		msg_exit("Error: invalid number of arguments", 2, EXIT_FAILURE);
	env->envp = envp;
	read_io(argv[1], argv[4], env);
	env->env_path = get_env_path(env->envp);
	if (!env->env_path)
		msg_exit("Error: could not retrieve environment path", 2, EXIT_FAILURE);
	if (dup2(env->fdin, 0) == -1)
		exit(EXIT_FAILURE);
	if (dup2(env->fdout, 1) == -1)
		msg_exit("Error: could not copy output file fd", 2, EXIT_FAILURE);
	pipex(argv[2], env);
	run_cmd(argv[3], env);
	return (0);
}
