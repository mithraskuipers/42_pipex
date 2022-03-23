/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 16:12:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/22 16:13:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_file(char	*file)
{
	if (access(file, F_OK) == 0)
		return (open(file, O_RDONLY, 0777));
	error_msg(file);
	return (-1);
}
