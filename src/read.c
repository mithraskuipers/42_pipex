/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:17:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_file(char	*file)
{
	if (access(file, F_OK) == 0)
		return (open(file, O_RDONLY, 0777));
	error_msg(file, ": no such file or directory");
	return (-1);
}
