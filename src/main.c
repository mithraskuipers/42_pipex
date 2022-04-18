/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:04:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/18 19:50:26 by mikuiper      ########   odam.nl         */
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
	{
		ft_putstr_fd("$RES_REAL: ambiguous redirect\n", 2);
		return (1);
	}
	env->envp = envp;

	/*/
	ft_putstr_fd(argv[1],1);
	ft_putstr_fd("\n",1);
	ft_putstr_fd(argv[4],1);
	ft_putstr_fd("\n",1);
	*/

	read_file(argv[1], argv[4], env);
	env->env_path = get_env_path(env->envp);
	if (!env->env_path)
		exit(1);
	if (dup2(env->fdin, 0) == -1)
		exit(1);
	if (dup2(env->fdout, 1) == -1)
		exit(1);
	pipex(argv[2], env);
	run_cmd(argv[3], env);
	return (0);
}
