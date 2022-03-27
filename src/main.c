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
	msg_return("error message", 1);
	return (0);
}

int		msg_return(char *cmd, int ret_status)
{
	ft_putstr_fd(cmd, 2);
	return(ret_status);
}

void	msg_exit(char *cmd, int exit_status)
{
	//ft_putstr_fd(cmd, 2);
	(void)cmd;
	exit(exit_status);
}