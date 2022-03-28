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

int	main(int argc, char **argv,	char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_pipex	*env;

	env = ft_calloc_new(1, sizeof(env));
	(void)env;
	//msg_return("error message", 1);
	msg_exit("exit message", 1);
	//while(1);
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