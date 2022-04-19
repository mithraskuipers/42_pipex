/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:20:15 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 07:24:14 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_cmd_error(char	*cmd, char *s, int fd)
{
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

void	msg_exit(char *s, int fd, int exit_code)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
	exit(exit_code);
}
