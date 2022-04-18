/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:17:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/18 20:06:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_file(char *infile_name, char *outfile_name, t_env *env)
{
	env->fdout = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (env->fdout == -1)
		exit(1);
	env->fdin = open(infile_name, O_RDONLY, 0777);
	if (env->fdin == -1)
		error_msg(infile_name, ": no such file or directory");
}

/*
void	read_file(char *infile_name, char *outfile_name, t_env *env)
{
	env->fdout = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (env->fdout == -1)
		exit(1);
	if (access(infile_name, F_OK) == 0)
	{
		env->fdin = open(infile_name, O_RDONLY, 0777);
		if (env->fdin == -1)
		{
			error_msg(infile_name, ": no such file or directory");
		}
	}
	else
	{
		error_msg(infile_name, ": no such file or directory");
	}
}
*/

/*
env->fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
if (env->fdout == -1)
	exit(1);
env->fdin = read_file(argv[1]);
*/