/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 21:01:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 21:01:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char	*cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
