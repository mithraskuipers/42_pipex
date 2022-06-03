/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/19 09:42:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_io(char *infile_name, char *outfile_name, t_env *env)
{
	env->fdin = open(infile_name, O_RDONLY, 0777);
	if (env->fdin == -1)
		msg_cmd_error(infile_name, ": no such file or directory");
	env->fdout = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (env->fdout == -1)
		exit(EXIT_FAILURE);
}
